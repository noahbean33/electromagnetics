# Computational electromagnetics in 2025: landscape, gaps, and opportunities for the HPC-native researcher

**The CEM field sits at a rare inflection point where hardware evolution, software stagnation, and emerging algorithmic paradigms have opened exploitable gaps that favor researchers with deep systems programming and HPC skills over traditional EM theorists.** GPU memory bandwidth — not compute — now gates FDTD performance, yet most production codes still use naive memory access patterns. The open-source CEM ecosystem lacks a unified multi-solver platform, GPU-native FEM/BEM solvers, and any signal/power integrity tooling. Meanwhile, Rust has proven within 1.23% of Fortran on HPC benchmarks but has produced only proof-of-concept CEM codes, and RISC-V vector hardware is shipping with zero CEM software targeting it. These intersections — modern systems languages, emerging ISAs, and memory-system-aware algorithm design — represent greenfield territory with outsized publication and impact potential for an individual researcher.

---

## 1. The CEM research landscape: where the field stands in 2025

### Full-wave numerical methods remain the workhorses

**FDTD** continues to dominate broadband time-domain simulation. The authoritative 2023 Nature Reviews Methods Primer by Teixeira, Sarris, Simpson, Chew, and others from Ohio State, Toronto, Utah, and Purdue provides the definitive modern reference. Key recent advances include higher-order schemes achieving up to **order 16 in 1D and 12 in 2D** (Wei & Zhao, Michigan State), stable subgridding via model order reduction (Li & Triverio, Toronto, URSI AT-RASC 2024), and an MLIR/LLVM domain-specific compiler for portable FDTD optimization across Intel, AMD, and ARM CPUs (He & Markidis, KTH, arXiv:2504.09118, 2025). Unconditionally stable ADI-FDTD schemes continue development but sacrifice accuracy with large time steps. The fundamental open problems remain multiscale modeling spanning nanometer-to-centimeter structures, numerical dispersion at high frequencies, and GPU memory capacity limits for electrically large problems.

**FEM** has seen strong growth in Discontinuous Galerkin (DG-FEM) methods, with GPU-accelerated DGTD achieving ~78% execution time reduction for multiscale problems using third-order local time stepping (Mathematics, vol. 12, 2024). Isogeometric Analysis (IGA) using B-splines/NURBS is an emerging direction, particularly at TU Darmstadt (Schöps, Kurz) and EPFL (Buffa). Domain decomposition for FEM is advancing through rigorous DDM verification with basis functions up to fourth order (Harmon et al., IEEE TAP, 2023), led by J.-F. Lee (Ohio State) and Z. Peng (New Mexico). A comprehensive DDM survey appeared in Electromagnetic Science (vol. 3, 2025), covering integration with Maxwell's equations for VLSI circuits and antenna arrays.

**MoM/BEM** has evolved toward isogeometric formulations, with Chen et al. demonstrating reduced-order IGA-BEM for CAD-integrated shape optimization in electromagnetic scattering (Computer Methods in Applied Mechanics and Engineering, vol. 419, 2024). Randomized Cross Approximation (Heldring, Rius, UPC Barcelona) operates on the Green's function kernel directly, achieving lower ranks than standard ACA with O(N) complexity. Nonconforming mesh methods at material interfaces now allow independent meshing of domains (J. Computational and Applied Mathematics, 2024).

### Fast algorithms are pushing complexity boundaries

The **butterfly algorithm** family represents the most exciting algorithmic development. The tensor butterfly algorithm (Kielstra, Shi, Luo, Qian, Liu; SIAM Multiscale Modeling and Simulation, 2025) handles **512× larger tensors** than existing butterfly methods and runs **200× faster** for comparable sizes, extending O(n^d) complexity to multi-dimensional oscillatory integral operators. HOD-BF-compressed VIE solvers (Yücel, NTU Singapore) demonstrate 5× faster performance than H-matrices at N=1.6M unknowns with O(N log²N) construction cost. Butterfly algebra (Heldring & Rius, UPC Barcelona) achieves N log⁴N complexity for high-frequency MoM matrix factorization — a breakthrough beyond the N^(3/2) log N butterfly decomposition.

**MLFMA** implementations now solve problems with 41+ million unknowns, with GPU-accelerated versions achieving 5–20× speedup via OpenMP-CUDA hybrid programming. Wideband MLFMA using incomplete-leaf tree structures handles multiscale problems with wide dynamic range of mesh sizes. The key open problems are exascale implementations, community benchmark standards, and auto-tuning frameworks analogous to FFTW.

**H-matrices** continue developing, with H-LU direct solvers combined with overlapped DDM and MLFMA for monostatic RCS computation. However, HOD-BF consistently outperforms H-matrices: 5×/3.2× less CPU time and 3.2×/2.7× less memory for construction/inversion at N=1.6M unknowns. Leading groups include Hackbusch (MPI Leipzig), Börm (Kiel), and Y. Liu (LBNL).

**Randomized numerical linear algebra** is making inroads into CEM. Parallel hierarchical blocked ACA with randomized pivoting (Liu, Sid-Lakhdar, LBNL, 2020) and randomized butterfly construction schemes avoid expensive adaptive partial pivoting. The 2020 Acta Numerica review by Martinsson and Tropp provides the theoretical foundations applicable to CEM.

### ML/AI augmentation is maturing unevenly

**Neural operators** represent the most practical ML-CEM intersection. The Data-Aware FNO (DA-FNO, arXiv:2508.17238, 2025) achieves **7.5× speedup with ~92.5% accuracy** over FDTD for photonic simulation. PIC2O-Sim (APL Photonics, 2025) — a physics-inspired causality-aware neural operator — achieves **133× speedup** over single-process FDTD with 49.1% less prediction error and 23.5× fewer parameters than FNO. WINO (arXiv:2408.02971, 2024) introduces Fourier Group Convolution Shuffling for ~100× speedup over FDFD. The leading groups are Anandkumar/Li (Caltech) for FNO foundations, and Fan (Stanford) for photonic applications.

**PINNs for Maxwell's equations remain limited.** MaxwellNet (Lim & Psaltis, APL Photonics, 2022) works for aspheric micro-lenses. Domain-adaptive PINNs (IEEE, 2024) address material interfaces with learnable decomposition. But PINNs still struggle with 3D time-dependent Maxwell problems, high-frequency content, multi-scale media, and provide no formal error bounds. Training is unstable and convergence slow for realistic problems.

**Surrogate models for antenna optimization** are the most mature ML-CEM application. Koziel & Pietrenko-Dabrowska (Reykjavik/Gdansk) have produced extensive work using kriging metamodels with reduced-dimensionality surrogates, achieving competitive results over full-dimensionality ML. CNNs trained on 150,000 simulated datasets predict S-parameters while combined with binary PSO for inverse design.

**Differentiable EM solvers** are a significant development. FDTDX (arXiv:2412.18360, 2024) is an open-source JAX-based framework exploiting FDTD time-reversibility to **reduce memory by 98%** versus standard automatic differentiation, scaling to billions of grid cells across multiple GPUs. Tidy3D (Flexcompute) provides commercial differentiable FDTD with adjoint optimization, claiming 100× faster and 100× larger problems than conventional CPU solvers.

### Applications driving computational demand

**Massive MIMO and 6G** antenna arrays with thousands of elements present immense computational challenges. Björnson et al. (arXiv:2401.02844, 2024) describe Ultra-Massive MIMO where near-field effects mandate joint EM/circuit/signal-processing co-design, but full-wave simulation of entire arrays remains infeasible. **Reconfigurable Intelligent Surfaces (RIS)** face the same scale problem — no unified open platform exists for full EM-level RIS simulation at realistic scales.

**Signal integrity for advanced packaging** (chiplets, 2.5D/3D ICs) is becoming a critical application. The SPIRAL framework (ASP-DAC 2024) achieves 18–44× speedup for inter-chiplet serial link analysis. As Synopsys notes: "When talking from a chiplet to HBM, there's 1,024 bits simultaneously — you need to simulate the entire electromagnetics." Feature sizes shrinking while speeds increase above 10 GHz forces the shift from quasi-static to full-wave 3D EM simulation.

**Quantum computing for CEM** remains largely theoretical. The foundational HHL-based paper (Clader, Jacobs & Sprouse, PRL, 2013) showed exponential speedup in theory, but resource analysis (Scherer et al., 2016) reveals that "reduction by many orders of magnitude is necessary for the algorithm to become practical." NISQ-era variational approaches (VQLS, PVLS with GNN initialization) show interesting algorithmic ideas but no practical advantage over classical solvers. More productively, CEM is being applied *to* quantum hardware design — AWS Palace was developed specifically for superconducting qubit simulation.

---

## 2. HPC and parallel computing: the performance reality

### Memory bandwidth gates FDTD, not compute

The most important HPC fact in CEM is that **FDTD is definitively memory-bandwidth-bound**. Minkov, Fan et al. (Optics & Photonics News, Sept 2024) provide the definitive analysis: the basic Yee update requires **36 FLOPs/cell but 144 bytes/cell** (single precision), giving an arithmetic intensity of only **0.25 FLOP/byte**. On every modern GPU, the bandwidth term dominates performance. This means the NVIDIA H100 with 3.35 TB/s HBM3 bandwidth delivers dramatically better FDTD than CPUs — but raw TFLOPS are largely irrelevant.

A breakthrough 2025 paper proposes a **systolic FDTD update scheme** that circumvents this by decomposing computation into L1-cache-fitting subdomains, relegating global memory access to boundary values only. This achieves **~0.15 trillion cell updates per second (TCUPS) on a single NVIDIA H100** — a major advance representing algorithmic innovation at the memory-system level rather than brute-force compute scaling.

For **FEM**, the picture is mixed: assembly can be memory-bound, SpMV in iterative solves is memory-bound, but preconditioner application may be compute-bound. **MoM/MLFMA** is heterogeneous: far-field computation is compute-intensive while near-field is memory-intensive. These workload characteristics have profound implications for hardware selection and algorithm design.

### GPU scaling reaches 1000+ devices for EM

**FlashMP** (arXiv:2508.07193, 2025) represents the state-of-the-art in GPU-scaled CEM: a fast discrete transform-based preconditioner for Maxwell's equations tested on **AMD MI60 GPU clusters up to 1000 GPUs**, achieving **up to 16× reduction in iteration counts** versus Hypre baseline. BiCGSTAB achieves **84.1% parallel efficiency at 1000 GPUs**, outperforming GMRES (73.5%) because it has fixed per-iteration communication costs while GMRES's Arnoldi orthogonalization requires growing collective reductions.

Multi-GPU FDTD using NCCL for direct GPU-GPU communication (Applied Sciences, 2025) eliminates CPU data forwarding and PCIe bottlenecks. Three-level parallel FDTD (MPI+CUDA) achieves **105× speedup** for marine CSEM applications (Computers & Geosciences, 2024). Domain decomposition for the modified Born series solves Helmholtz problems of 3.28×10⁷ cubic wavelengths in 45 minutes on dual GPU with only ~10% overhead per added GPU.

### Hardware landscape: MI300X bandwidth versus GH200 unified memory

| Feature | NVIDIA H100/GH200 | AMD MI300X | Intel Xe (Aurora) |
|---------|-------------------|------------|-------------------|
| HBM capacity | 80–96 GB (HBM3/3e) | **192 GB** (HBM3) | 128 GB (HBM2e) |
| Memory bandwidth | 3.35 TB/s | **5.3 TB/s** | 3.2 TB/s |
| FP64 TFLOPS | 34 | **61.3** | 52 |
| CEM software ecosystem | **Mature (CUDA)** | Growing (ROCm/HIP) | Emerging (SYCL) |

For memory-bound FDTD, the **AMD MI300X's 5.3 TB/s** bandwidth is theoretically 1.6× superior to H100. FluidX3D lattice Boltzmann benchmarks show MI300X **1.86× faster** than H100 PCIe. However, CUDA software maturity gives H100 practical advantages — MI300X achieves only ~45% of theoretical peak utilization versus H100's ~93%.

The **NVIDIA GH200** is transformative for capacity-limited CEM: 900 GB/s NVLink-C2C between ARM CPU and Hopper GPU with unified memory eliminates explicit data management. Simulations exceeding GPU HBM can seamlessly spill into 480 GB LPDDR5X. LSMS density functional theory achieves **~3× speedup** using automatic first-touch migration.

**Intel Gaudi** accelerators focus on AI training/inference with negligible CEM presence. Intel's HPC GPU effort centers on Ponte Vecchio (Xe HPC) in Aurora using oneAPI/SYCL.

### Key CEM software with GPU acceleration

**Palace** (AWS, Apache 2.0) is the most feature-rich open-source EM solver, built on MFEM and libCEED with CUDA/HIP GPU support. It features matrix-free p-multigrid with high-order operator partial assembly and scales to thousands of cores. **gprMax** achieves up to **3405 Mcells/s** on Pascal GPU (30× faster than OpenMP CPU) but is specialized for ground-penetrating radar. **MFEM** (LLNL) provides the GPU-accelerated FEM foundation — the 2025 ACM Gordon Bell Prize winner used MFEM on El Capitan. **PETSc** (Argonne) supports CUDA, HIP, SYCL, and Kokkos backends with exascale testing on Frontier and Aurora.

---

## 3. Rust and RISC-V: the systems programming frontier in CEM

### Rust reaches Fortran-class performance with zero CEM presence

Rust's viability for scientific computing is now empirically established. The **NAS Parallel Benchmarks in Rust** (arXiv:2502.15536, Feb 2025) demonstrate Rust is **1.23% slower than Fortran and 5.59% faster than C++** across 8 kernels. A computational physics case study (arXiv:2410.19146, Oct 2024) showed Rust achieving **up to 5.6× improvement over C++** in laser-plasma interaction simulation with easy parallelization via Rayon. SC'23 demonstrated reimplementing Open MPI intra-node communication in Rust with **performance approaching highly-optimized C**.

Yet CEM-specific Rust codes are minimal:

- **FEM_2D** (Corrado, Harmon, Notaroš, Ilić; Colorado State; JOSS 2023): A Rust library for 2D FEM with hp-refinement supporting Maxwell eigenvalue problems and H(curl)/H(div) discretizations. Research-grade, 2D only.
- **Bempp-rs** (Betcke, Scroggs, Kailasa; UCL): Rewrite of established BEM library in Rust. Supports Laplace and Helmholtz; **Maxwell support actively in development**. Uses RLST (Rust Linear Solver Toolbox).
- **rems**: A 1D-only FDTD proof-of-concept.

The Rust scientific computing ecosystem is coalescing around an annual workshop (scientificcomputing.rs, organized by UCL and CU Boulder), monthly newsletter, and key libraries: **faer** (high-performance pure-Rust linear algebra competitive with LAPACK, under JOSS review), **Rayon** (data parallelism with guaranteed data-race freedom, ~4.6% SLOC overhead versus OpenMP's ~5.4%), **rsmpi** (MPI bindings with a 2025 proposal for compile-time type-safe MPI), and **wgpu** (cross-platform GPU compute via WebGPU). GPU computing remains early: rust-gpu compiles Rust to SPIR-V and as of July 2025 runs on "every GPU" including CUDA, but is not production-ready for HPC.

### RISC-V vector hardware ships with zero CEM software

**RVV 1.0** was ratified in November 2021 with variable-length vector registers (VLEN configurable per implementation), architecturally similar to ARM SVE's vector-length agnostic design. Hardware shipping RVV 1.0 includes SpacemiT K1 and Kendryte K230, though earlier chips (SG2042, Allwinner D1) only support the incompatible draft RVV 0.7.1.

The European HPC ecosystem is making major RISC-V investments. The **EPI Vitruvius+ VPU** supports 256 double-precision elements per vector register (**16,384-bit VLEN**), with EPAC1.0 as the first European RISC-V vector CPU to boot Linux. The **DARE project** (launched March 2025, 38 partners, coordinated by BSC) targets general-purpose RISC-V processors with AI and vectorial accelerators competitive with non-EU solutions. **Esperanto Technologies** ships ET-SoC-1 with 1,093 RISC-V cores and 512-bit vector units, partnering with NEC for next-gen HPC chips.

Benchmarks are promising: HPCG on RISC-V vector hardware achieves **near maximum memory bandwidth utilization** (ScienceDirect, 2023). The RAJA Performance Suite on Allwinner D1 shows "reasonable vectorization speedup" (ISC HPC 2023). SeisSol on the EPAC architecture achieves significant speedup with batched GEMM optimization. However, **no CEM codes have been optimized for RISC-V** — only fdtd3d (GitHub) lists RISC-V as a supported target.

The Rust-RISC-V intersection is virtually unexplored. Rust supports riscv64gc targets at Tier 2. The 'V' extension feature flag exists since 2022, but **stable SIMD intrinsics for RVV are NOT available in Rust**. faer explicitly plans RVV optimizations once intrinsics stabilize. A single 2019 ACM workshop paper demonstrated Rust+LLVM for RISC-V V extensions with BLAS-style computations.

---

## 4. Gap analysis: where the opportunities are

### Algorithmic gaps exploitable by HPC expertise

**Memory-system-aware CEM algorithms are grossly underexplored.** The systolic FDTD scheme (2025) demonstrates that cache-aware decomposition can transform FDTD performance, yet this approach has not been applied to FEM assembly, BEM matrix construction, or MLFMA translation/interpolation operations. An HPC researcher understanding roofline models, cache hierarchies, and data layout could systematically apply cache-oblivious and cache-tiling techniques across CEM methods.

**Auto-tuning frameworks for CEM are nonexistent.** FFTW transformed FFT performance through auto-tuning; no equivalent exists for FMM octree tuning, FDTD tiling parameters, FEM assembly strategies, or sparse solver algorithm selection. The CEM community lacks the systems expertise to build such frameworks.

**Portable performance across GPU vendors is a major gap.** Most CEM GPU codes are CUDA-only. ROCm/HIP ports exist for PETSc and MFEM but CEM-specific codes (gprMax, most research FDTD implementations) lack AMD or Intel GPU support. Performance portability layers (Kokkos, RAJA, SYCL) are underutilized in CEM.

### Software ecosystem gaps

**The open-source CEM ecosystem has glaring holes:**

- No unified multi-solver platform combining FEM + FDTD + MoM with integrated pre/post-processing
- No open-source signal/power integrity tooling (commercial dominance by Ansys SIwave, Cadence Clarity)
- No open-source EMC/EMI analysis platform
- Limited antenna-specific workflows in open-source tools (array design, pattern synthesis, RCS computation)
- No open-source EM-thermal co-simulation with production coupling
- Poor interoperability between existing tools (no standard model exchange format)
- Palace (the most capable open-source solver) has no native GUI — only third-party WELSIM

**The educational gap is significant.** Existing CEM courses focus on EM theory with toy implementations. No resources bridge CEM theory with modern HPC practice — GPU kernel optimization, distributed computing, memory-aware algorithm design, or modern language toolchains.

### Intersection opportunities uniquely suited to the target researcher profile

**Rust + CEM**: No production-grade 3D FDTD, FEM, or MoM code exists in Rust. FEM_2D is 2D-only; Bempp-rs lacks Maxwell support; rems is 1D. The combination of Rust's memory safety (eliminating data races in parallel CEM), near-Fortran performance, and modern tooling (cargo, crates.io, integrated testing) creates an opportunity for a researcher to build reference implementations that attract both the CEM and Rust scientific computing communities.

**RISC-V + CEM**: Zero CEM codes are optimized for RISC-V vector extensions. RISC-V's extensibility allows custom instruction extensions for stencil operations (critical for FDTD), complex number arithmetic (fundamental to frequency-domain CEM), and sparse matrix operations (key for FEM/BEM). The EPI EPAC already includes a Stencil accelerator — direct applicability to FDTD.

**ML + HPC + CEM**: Differentiable CEM solvers (FDTDX) and neural operators (FNO, PIC2O-Sim) are GPU-native but lack multi-GPU scaling studies, RISC-V targets, or Rust implementations. ML-augmented preconditioners for CEM linear systems are extremely nascent despite clear theoretical motivation.

---

## 5. Concrete research topics and project recommendations

The following recommendations are ordered by feasibility and expected impact for an independent researcher with strong HPC/systems programming skills, BS-level mathematics, and consumer-grade hardware.

### 1. Memory-system-aware FDTD: a Rust reference implementation

Build a 3D FDTD solver in Rust that systematically exploits cache hierarchy through temporal blocking and systolic-style update schemes. Benchmark against gprMax and MEEP on identical problems. Publish the cache-tiling analysis and roofline model characterization as a standalone contribution, then release the code as open source. **Why this works**: The systolic FDTD paper (2025) showed 0.15 TCUPS on H100 through cache awareness alone — reproducing and extending this in Rust on consumer GPUs via wgpu would be novel. Consumer hardware (RTX 4090 with 1 TB/s bandwidth) is sufficient. The Rust CEM community (FEM_2D, Bempp-rs) provides collaboration opportunities. Target venues: Computer Physics Communications, IEEE TAP.

### 2. RISC-V vector extension benchmarking for CEM kernels

Port core CEM computational kernels — Yee cell update, SpMV for FEM, Green's function evaluation for BEM, FFT butterfly — to RISC-V using RVV intrinsics (via C or assembly, since Rust RVV intrinsics are unstable). Benchmark on SpacemiT K1 or MILK-V boards against ARM SVE (Graviton) and x86 AVX-512. Publish a roofline analysis comparing memory bandwidth utilization across ISAs for each kernel type. **Why this works**: The EPCC RISC-V testbed provides remote access to hardware. No such CEM-focused ISA comparison exists. Results directly inform the EPI/DARE communities. Target venues: ISC HPC, SC workshops, IEEE Micro.

### 3. Portable GPU compute for FDTD via wgpu/WebGPU

Implement a 3D FDTD solver using wgpu compute shaders (WGSL) that runs identically on NVIDIA, AMD, Intel, and Apple GPUs — plus in web browsers via WebGPU. Demonstrate that the portability penalty versus CUDA is quantifiable and often acceptable. **Why this works**: No CEM solver runs on Apple Silicon GPUs or in browsers. WebGPU-based FDTD would serve both research and education. The 2025 Amazon book "GPU Computing with wgpu" provides starting infrastructure. Consumer hardware is the target by design. Target venues: JOSS (software paper), IEEE AP-S conference, plus significant educational impact.

### 4. faer-powered sparse linear algebra for CEM on RISC-V

Extend the faer library with sparse matrix formats (CSR, ELLPACK, BSR) and iterative solvers (CG, BiCGSTAB, GMRES) optimized for CEM workloads, with RVV-optimized kernels when intrinsics stabilize. Benchmark against PETSc and Eigen on CEM-derived matrices from the SuiteSparse Matrix Collection. **Why this works**: faer's maintainer explicitly plans RVV optimization. No pure-Rust sparse solver ecosystem exists for CEM-scale problems. Contributing to faer provides leverage through the existing Rust scientific computing community. Target venues: JOSS, ACM TOMS, Scientific Computing in Rust workshop.

### 5. Open-source antenna analysis toolkit

Build a Python-Rust antenna analysis tool that wraps Palace or OpenEMS with antenna-specific post-processing: far-field patterns, gain computation, array factor synthesis, RCS calculation, and S-parameter extraction. Include parametric optimization using Bayesian methods. **Why this works**: This is the most frequently cited gap in open-source CEM — commercial tools (HFSS, CST, FEKO) dominate antenna design because open-source tools lack antenna workflows. A well-documented tool with tutorials would have outsized educational and community impact. Consumer hardware is sufficient for small-to-medium antenna problems. Target: JOSS publication plus tutorial content.

### 6. Differentiable FDTD in Rust with GPU backend

Implement an adjoint-method-based differentiable FDTD solver in Rust, leveraging the time-reversibility trick (98% memory reduction demonstrated by FDTDX) with wgpu or CUDA backend. Enable gradient-based topology optimization for photonic and antenna structures. **Why this works**: FDTDX (JAX) and Tidy3D (commercial) are the only options. A Rust implementation would offer deterministic performance, avoid Python/JAX overhead, and provide a path to RISC-V. The mathematical requirements (adjoint method, chain rule through Yee updates) are within BS-level linear algebra. Target venues: Optics Express, ACS Photonics, Computer Physics Communications.

### 7. ML-augmented preconditioning for CEM linear systems

Train lightweight neural networks to predict near-optimal preconditioner parameters (ILU fill level, AMG coarsening strategy, polynomial degree) based on problem features (mesh statistics, frequency, material contrast). Benchmark preconditioner selection time versus iteration count reduction on a suite of CEM problems from Palace and MFEM. **Why this works**: ML preconditioners for CEM are described as "very nascent" in the literature. This is an ML-HPC intersection requiring more software engineering than EM theory. Consumer GPU (RTX 4090) is sufficient for both the training and CEM solves. Target venues: SIAM Journal on Scientific Computing, NeurIPS ML4PS workshop.

### 8. CEM workload characterization for emerging architectures

Create a comprehensive benchmark suite of CEM kernel microbenchmarks (stencil, SpMV, dense GEMM, FFT, tree traversal) and full-application proxies, with detailed roofline analysis on consumer hardware: AMD Ryzen + RTX 4090 (CUDA), Apple M-series (wgpu/Metal), RISC-V boards (RVV). Publish an architecture-aware CEM workload guide that maps solver types to hardware characteristics. **Why this works**: No such guide exists. The CEM community selects hardware based on vendor marketing, not workload analysis. This is pure systems/architecture research requiring minimal EM theory. Target venues: IEEE Micro, SC conference, ISPASS.

### 9. Signal integrity simulation foundations in Rust

Begin building open-source S-parameter extraction and transmission line analysis tools in Rust — starting with 2D cross-sectional solvers (Laplace and Helmholtz) using FEM_2D as a foundation, then extending to quasi-static 3D via BEM. **Why this works**: The commercial SI/PI market ($500M+) has zero open-source competition. Even basic tools (impedance extraction from PCB cross-sections) would be valuable. The chiplet/advanced packaging trend (UCIe at 32 Gbps) is driving demand beyond the existing commercial tool capacity. This has both research publication and commercial consulting potential. Target: JOSS, DesignCon, IEEE EPEPS.

### 10. Educational content bridging CEM theory and modern HPC practice

Create a tutorial series (or small book) implementing CEM methods from scratch in Rust: 1D/2D/3D FDTD, FEM for waveguides, MoM for wire antennas — with emphasis on performance engineering (SIMD, cache tiling, GPU offload, distributed computing). Publish as open educational resource alongside benchmark comparisons against established tools. **Why this works**: Every CEM textbook implements in MATLAB or legacy Fortran. No resource connects CEM with modern systems programming. The educational gap is universally acknowledged. Even partial completion (e.g., FDTD-focused) would attract significant attention from both CEM and Rust communities. Target: self-published with arXiv companion paper, potential IEEE AP-S magazine article.

---

## Key research groups and institutional landscape

The CEM field concentrates around identifiable centers of excellence worth tracking for collaboration and positioning:

**Numerical methods and fast algorithms**: Ohio State (Lee, Teixeira — DDM, FDTD, FEM), Purdue (Chew — integral equations), UIUC (Jin — FETD/DGTD), UPC Barcelona (Heldring, Rius — butterfly algorithms, randomized methods), LBNL (Y. Liu — parallel butterfly/H-matrix), U. Michigan (Michielssen — butterfly direct solvers), NTU Singapore (Yücel — HOD-BF for VIE), EPFL (Buffa — IGA foundations).

**HPC and GPU acceleration**: KTH Stockholm (Markidis — FDTD compilers), LLNL (Kolev — MFEM), Argonne (PETSc team), Flexcompute/Stanford (Fan — Tidy3D), AWS CQC (Palace). FlashMP team demonstrated 1000-GPU scaling.

**ML-CEM intersection**: Brown (Karniadakis — PINNs), Caltech (Anandkumar — FNO), Stanford (Fan — differentiable photonics), Ohio State (Teixeira — DL for inverse scattering), Reykjavik/Gdansk (Koziel — surrogate-assisted antenna optimization), Trento (Salucci — AI for inverse scattering).

**Rust scientific computing**: UCL (Betcke, Scroggs — Bempp-rs, RLST), CU Boulder (Brown — JOSS editorial), Colorado State (Notaroš — FEM_2D). The community is small enough that meaningful contributions gain immediate visibility.

**RISC-V HPC**: BSC (DARE coordination), EPI consortium (Vitruvius+), EPCC Edinburgh (RISC-V testbed), Esperanto Technologies (commercial RISC-V HPC).

---

## Conclusion: strategic positioning for maximum impact

The most impactful research strategy for a researcher with this profile is **not** to compete on EM theory — which requires PhD-level specialization — but to exploit the persistent gap between CEM algorithm research and production-quality implementation. The CEM community produces elegant algorithms but implements them in legacy Fortran/C++ with naive memory access patterns, no portability, and no modern software engineering. Three vectors offer the highest return:

**First**, memory-system-aware algorithm implementation. The systolic FDTD result proves that cache-conscious design can transform CEM performance. Extending this systematically across FEM, BEM, and FMM — with rigorous roofline analysis and open-source release — is novel, publishable, and immediately useful.

**Second**, the Rust-CEM intersection is a near-vacuum. FEM_2D and Bempp-rs are the only serious efforts, both from small academic groups. A well-engineered 3D FDTD or MoM solver in Rust would be a community first, attracting attention from both CEM and scientific Rust audiences. The NPB benchmarks eliminate the "Rust is too slow" objection.

**Third**, RISC-V CEM benchmarking positions the researcher at the intersection of European HPC investment (DARE, EPI) and electromagnetic simulation. The RISC-V HPC community actively seeks application workloads to justify hardware development — CEM kernels with their varied memory/compute profiles provide excellent benchmarking diversity.

The compounding effect is key: a Rust FDTD solver that runs on RISC-V, x86, and ARM with GPU offload via wgpu would be simultaneously a contribution to CEM, to the Rust scientific ecosystem, to RISC-V application benchmarking, and to performance portability research — one codebase generating publications across four communities.