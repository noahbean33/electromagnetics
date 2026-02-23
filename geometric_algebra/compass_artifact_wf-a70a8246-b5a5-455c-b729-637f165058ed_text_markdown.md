# Geometric Algebra and Maxwell's Equations: A Comprehensive Mathematical Reference

**Geometric algebra unifies the inner and outer products of vectors into a single invertible geometric product, enabling all four of Maxwell's equations to be written as the single equation ∇F = J.** This formulation, first developed by David Hestenes in 1966 and refined by the Cambridge group in the 1990s, reveals the deep geometric structure of electromagnetism while simplifying computation. The framework builds on 19th-century work by Grassmann, Hamilton, and Clifford, and provides a coordinate-free language that naturally encompasses scalars, vectors, bivectors, rotors, and spinors within one algebraic system.

This reference covers the algebraic foundations of geometric algebra (GA), constructs the algebras G(3) and G(1,3), derives Maxwell's equations in both formulations, and develops advanced applications including Lorentz transformations, the stress-energy tensor, and spinor theory.

---

## Part I: Foundations of geometric algebra

### 1.1 Historical lineage from Grassmann to Hestenes

Geometric algebra synthesizes three major 19th-century mathematical innovations. **Hermann Grassmann** published *Die lineale Ausdehnungslehre* in 1844, introducing the exterior (wedge) product a∧b = −b∧a as a coordinate-free algebraic method for computing with subspaces. **William Rowan Hamilton** discovered quaternions on October 16, 1843, creating a four-dimensional algebra with basis {1, i, j, k} satisfying i² = j² = k² = ijk = −1 that elegantly encodes three-dimensional rotations.

**William Kingdon Clifford** unified these two frameworks in his 1878 paper "Applications of Grassmann's Extensive Algebra," combining Grassmann's exterior algebra with Hamilton's notion of directed numbers that square to scalars. Clifford named the result "geometric algebra," but died at age 33 in 1879 before fully developing it. The system lay largely dormant for nearly a century. **David Hestenes** revived geometric algebra for physics with his 1966 monograph *Space-Time Algebra*, reformulating the Dirac equation and Maxwell's equations in the Clifford algebra Cl(1,3). His 1984 book with Garret Sobczyk, *Clifford Algebra to Geometric Calculus*, extended the framework to include differentiation and integration. Chris Doran, Anthony Lasenby, and Stephen Gull at Cambridge further developed applications from the 1990s onward, culminating in *Geometric Algebra for Physicists* (2003).

### 1.2 The geometric product and its decomposition

The central object in geometric algebra is the **geometric product** of vectors, defined axiomatically for vectors a, b in a real vector space V equipped with a symmetric bilinear form:

- **Associativity**: a(bc) = (ab)c
- **Distributivity**: a(b + c) = ab + ac and (a + b)c = ac + bc
- **Contraction**: a² = aa = a · a ∈ ℝ (the quadratic form)

From these axioms alone, two fundamental identities follow. Adding and subtracting ab and ba:

$$a \cdot b = \tfrac{1}{2}(ab + ba) \qquad \text{(inner product — symmetric, scalar-valued)}$$

$$a \wedge b = \tfrac{1}{2}(ab - ba) \qquad \text{(outer product — antisymmetric, bivector-valued)}$$

The geometric product therefore decomposes as:

$$\boxed{ab = a \cdot b + a \wedge b}$$

This single equation is the cornerstone of geometric algebra. The inner product measures collinearity (magnitude of parallel components), while the outer product measures the oriented area swept out by the two vectors. For **parallel vectors** (a ∥ b), the wedge product vanishes and ab = a·b = ba (vectors commute). For **orthogonal vectors** (a ⊥ b), the dot product vanishes and ab = a∧b = −ba (vectors anticommute).

The geometric product is **invertible** for any nonzero vector: if a² ≠ 0, then a⁻¹ = a/a². This invertibility is a key advantage over the cross product and wedge product alone, neither of which is invertible.

For two vectors with angle θ between them, the geometric product takes the polar form:

$$ab = |a||b|(\cos\theta + \hat{B}\sin\theta) = |a||b|\,e^{\hat{B}\theta}$$

where B̂ is the unit bivector of the plane containing a and b. This Euler-like formula connects the geometric product directly to rotations.

### 1.3 Blades, multivectors, and grade structure

The outer product generalizes to higher grades. A **k-blade** is the outer product of k linearly independent vectors:

$$B_k = a_1 \wedge a_2 \wedge \cdots \wedge a_k$$

representing an oriented k-dimensional subspace. A **multivector** is a general element of the algebra, expressible as a sum of blades of different grades. In an n-dimensional space, the grade structure is:

| Grade k | Name | Geometric meaning | Dimension C(n,k) |
|---------|------|-------------------|-------------------|
| 0 | Scalar | Magnitude | 1 |
| 1 | Vector | Directed line segment | n |
| 2 | Bivector | Oriented plane element | n(n−1)/2 |
| 3 | Trivector | Oriented volume element | n(n−1)(n−2)/6 |
| ⋮ | ⋮ | ⋮ | ⋮ |
| n | Pseudoscalar | Oriented n-volume | 1 |

The total dimension of the algebra is **2ⁿ** (sum of all binomial coefficients). Every multivector M decomposes uniquely into homogeneous components:

$$M = \langle M \rangle_0 + \langle M \rangle_1 + \langle M \rangle_2 + \cdots + \langle M \rangle_n$$

where ⟨M⟩ₖ denotes the **grade-k projection**. For the geometric product of a grade-r blade Aᵣ with a grade-s blade Bₛ:

$$A_r B_s = \langle A_r B_s \rangle_{|r-s|} + \langle A_r B_s \rangle_{|r-s|+2} + \cdots + \langle A_r B_s \rangle_{r+s}$$

The lowest-grade part is the generalized inner product, and the highest-grade part is the outer product:

$$A_r \cdot B_s = \langle A_r B_s \rangle_{|r-s|}, \qquad A_r \wedge B_s = \langle A_r B_s \rangle_{r+s}$$

### 1.4 The algebra G(3): basis elements and multiplication table

The geometric algebra of three-dimensional Euclidean space, **G(3) = Cl(3,0)**, is generated by three orthonormal basis vectors {e₁, e₂, e₃} satisfying:

$$e_i e_j + e_j e_i = 2\delta_{ij}$$

This gives eᵢ² = 1 and eᵢeⱼ = −eⱼeᵢ for i ≠ j. The algebra is **8-dimensional** with the basis:

| Grade | Basis elements | Count |
|-------|---------------|-------|
| 0 | 1 | 1 |
| 1 | e₁, e₂, e₃ | 3 |
| 2 | e₁₂, e₂₃, e₃₁ | 3 |
| 3 | I = e₁₂₃ | 1 |

where eᵢⱼ ≡ eᵢeⱼ and I = e₁e₂e₃ is the **pseudoscalar**. The conventional cyclic ordering {e₁₂, e₂₃, e₃₁} is used, noting that e₃₁ = e₃e₁ = −e₁e₃.

A general multivector in G(3) takes the form:

$$M = \alpha + (a_1 e_1 + a_2 e_2 + a_3 e_3) + (b_{12} e_{12} + b_{23} e_{23} + b_{31} e_{31}) + \beta I$$

with eight real coefficients α, aᵢ, bᵢⱼ, β ∈ ℝ.

**Complete multiplication table for G(3)** (row × column):

| × | 1 | e₁ | e₂ | e₃ | e₁₂ | e₂₃ | e₃₁ | I |
|---|---|----|----|----|----|----|----|---|
| **1** | 1 | e₁ | e₂ | e₃ | e₁₂ | e₂₃ | e₃₁ | I |
| **e₁** | e₁ | 1 | e₁₂ | −e₃₁ | e₂ | I | −e₃ | e₂₃ |
| **e₂** | e₂ | −e₁₂ | 1 | e₂₃ | −e₁ | e₃ | I | e₃₁ |
| **e₃** | e₃ | e₃₁ | −e₂₃ | 1 | I | −e₂ | e₁ | e₁₂ |
| **e₁₂** | e₁₂ | −e₂ | e₁ | I | −1 | −e₃₁ | e₂₃ | −e₃ |
| **e₂₃** | e₂₃ | I | −e₃ | e₂ | e₃₁ | −1 | −e₁₂ | −e₁ |
| **e₃₁** | e₃₁ | e₃ | I | −e₁ | −e₂₃ | e₁₂ | −1 | −e₂ |
| **I** | I | e₂₃ | e₃₁ | e₁₂ | −e₃ | −e₁ | −e₂ | −1 |

**Key derived results from the table**:

- **Bivector squares**: e₁₂² = e₁e₂e₁e₂ = −e₁²e₂² = **−1**. Similarly e₂₃² = e₃₁² = **−1**. Bivectors in G(3) behave like imaginary units.
- **Pseudoscalar square**: I² = (−1)^(3·2/2) · e₁²e₂²e₃² = (−1)³ · 1 = **−1**.
- **Pseudoscalar commutation**: I **commutes** with all elements of G(3). For any basis vector eₖ, moving eₖ through the other two vectors in I = e₁e₂e₃ requires exactly two anticommutation swaps, yielding (−1)² = +1. This property is specific to odd-dimensional spaces.

### 1.5 The pseudoscalar, duality, and the cross product

The pseudoscalar I = e₁₂₃ provides a **duality map** between grade-k and grade-(3−k) elements via multiplication:

$$Ie_1 = e_{23}, \qquad Ie_2 = e_{31}, \qquad Ie_3 = e_{12}$$

Since I² = −1, the inverse is I⁻¹ = −I, and the inverse duality mapping is:

$$I^{-1}e_{23} = e_1, \qquad I^{-1}e_{31} = e_2, \qquad I^{-1}e_{12} = e_3$$

The traditional **cross product** emerges as the dual of the wedge product:

$$\boxed{a \times b = -I(a \wedge b) = (a \wedge b)I^{-1}}$$

This reveals the cross product's true nature: it is not a vector operation per se, but the Hodge dual of the naturally bivector-valued wedge product. The cross product exists only in three dimensions precisely because that is where the duality maps bivectors to vectors.

The **even subalgebra** G⁺(3) = span{1, e₁₂, e₂₃, e₃₁} is four-dimensional and isomorphic to the **quaternions** ℍ under the identification e₁₂ ↔ k, e₃₁ ↔ j, e₂₃ ↔ i (with e₁₂e₃₁ = e₂₃ etc., matching ijk = −1 after appropriate sign choices).

### 1.6 Reversion, grade involution, and Clifford conjugation

Three important involutions act on multivectors in geometric algebra.

**Reversion** (denoted M̃ or M†) reverses the order of all vector factors in every product:

$$(a_1 a_2 \cdots a_k)\tilde{} = a_k \cdots a_2 a_1$$

It is an anti-automorphism: (AB)~ = B̃Ã. On a grade-k element, reversion multiplies by the sign factor (−1)^(k(k−1)/2):

| Grade | 0 | 1 | 2 | 3 | 4 | 5 |
|-------|---|---|---|---|---|---|
| Sign  | + | + | − | − | + | + |

The pattern repeats with period 4: {+, +, −, −, +, +, −, −, ...}.

**Grade involution** (denoted M̂) negates every vector factor, equivalent to multiplying grade-k parts by (−1)ᵏ:

$$\hat{M} = \sum_k (-1)^k \langle M \rangle_k$$

It is an automorphism: (AB)^ = ÂB̂.

**Clifford conjugation** (denoted M̄) combines both operations: M̄ = (M̃)^ = (M̂)~. On grade-k elements, it multiplies by (−1)^(k(k+1)/2), giving the sign pattern {+, −, −, +, +, −, −, +, ...}.

**Summary for G(3)**:

| Component | Grade | M̃ | M̂ | M̄ |
|-----------|-------|-----|-----|-----|
| Scalar α | 0 | +α | +α | +α |
| Vector a | 1 | +a | −a | −a |
| Bivector B | 2 | −B | +B | −B |
| Pseudoscalar βI | 3 | −βI | −βI | +βI |

### 1.7 Rotors, reflections, and the sandwich product

Geometric algebra provides an elegant, dimension-independent framework for reflections and rotations through algebraic products.

**Reflection.** The reflection of a vector v in the hyperplane perpendicular to unit vector n̂ (where n̂² = 1) is:

$$\boxed{v' = -\hat{n}\,v\,\hat{n}}$$

This negates the component of v parallel to n̂ while preserving perpendicular components. To verify: decompose v = v∥ + v⊥. Since v∥ ∥ n̂, they commute: n̂v∥ = v∥n̂. Since v⊥ ⊥ n̂, they anticommute: n̂v⊥ = −v⊥n̂. Then −n̂vn̂ = −n̂(v∥ + v⊥)n̂ = −v∥n̂² + v⊥n̂² = −v∥ + v⊥.

**Rotation.** A rotation is the composition of two reflections. If the reflecting hyperplanes have unit normals m̂ and n̂, the combined transformation is:

$$v' = (\hat{n}\hat{m})\,v\,(\hat{n}\hat{m})\tilde{} = R\,v\,\tilde{R}$$

where **R = n̂m̂ is a rotor**. The rotation angle is **twice** the angle between the mirror planes, and the rotation plane is the plane containing m̂ and n̂.

In general, a rotor for rotation by angle θ in the plane of unit bivector B̂ (where B̂² = −1) is:

$$\boxed{R = e^{-\hat{B}\theta/2} = \cos(\theta/2) - \hat{B}\sin(\theta/2)}$$

The rotation acts via the **sandwich product**:

$$v' = R\,v\,\tilde{R}$$

The reverse of the rotor is R̃ = cos(θ/2) + B̂ sin(θ/2), and the normalization condition RR̃ = 1 holds automatically. Rotors compose by multiplication: two successive rotations R₁ then R₂ give the combined rotor R₂R₁, and **every multivector** (not just vectors) transforms the same way: M′ = RMR̃.

In G(3), a general rotor has the form R = a₀ + a₁e₁₂ + a₂e₂₃ + a₃e₃₁ with the constraint a₀² + a₁² + a₂² + a₃² = 1, which is precisely the structure of a **unit quaternion**.

---

## Part II: The spacetime algebra G(1,3)

### 2.1 Basis vectors, metric, and the 16-dimensional structure

The **Spacetime Algebra** (STA) is the geometric algebra G(1,3) = Cl(1,3)(ℝ) of Minkowski spacetime with signature (+,−,−,−). It is generated by four orthonormal basis vectors {γ₀, γ₁, γ₂, γ₃} satisfying:

$$\gamma_\mu \gamma_\nu + \gamma_\nu \gamma_\mu = 2\eta_{\mu\nu}, \qquad \eta = \text{diag}(+1,-1,-1,-1)$$

So γ₀² = +1 (timelike), γᵢ² = −1 for i = 1,2,3 (spacelike), and γ_μγ_ν = −γ_νγ_μ for μ ≠ ν. The algebra is **2⁴ = 16-dimensional**:

| Grade | Basis elements | Count | Name |
|-------|---------------|-------|------|
| 0 | 1 | 1 | Scalar |
| 1 | γ₀, γ₁, γ₂, γ₃ | 4 | Vectors |
| 2 | γ₀₁, γ₀₂, γ₀₃, γ₁₂, γ₂₃, γ₃₁ | 6 | Bivectors |
| 3 | γ₀₁₂, γ₀₁₃, γ₀₂₃, γ₁₂₃ | 4 | Trivectors |
| 4 | I = γ₀₁₂₃ | 1 | Pseudoscalar |

The **STA pseudoscalar** is I = γ₀γ₁γ₂γ₃ with:

$$I^2 = (-1)^{4\cdot3/2}\,\gamma_0^2\gamma_1^2\gamma_2^2\gamma_3^2 = (+1)(+1)(-1)(-1)(-1) = \mathbf{-1}$$

Unlike in G(3), the pseudoscalar in STA **anticommutes** with vectors and trivectors (odd-grade elements) and **commutes** with scalars, bivectors, and pseudoscalars (even-grade elements). This distinction arises because STA has even dimension n = 4.

The **reciprocal basis** vectors are γ⁰ = γ₀ and γⁱ = −γᵢ (following from the metric: γ^μ = η^(μμ)γ_μ).

### 2.2 Relative vectors and the spacetime split

The **relative vectors** (or Pauli vectors) are defined as bivectors in STA:

$$\sigma_i = \gamma_i \gamma_0 \qquad (i = 1,2,3)$$

Despite being grade-2 objects in STA, the σᵢ satisfy the same algebra as the G(3) basis vectors:

$$\sigma_i \sigma_j + \sigma_j \sigma_i = 2\delta_{ij}$$

The σᵢ generate the even subalgebra G⁺(1,3) ≅ G(3,0), establishing a natural embedding of three-dimensional geometry within spacetime. The spatial pseudoscalar is σ₁σ₂σ₃ = I (identical to the STA pseudoscalar).

The **spacetime split** of any spacetime vector p relative to observer γ₀ separates temporal and spatial parts:

$$p\gamma_0 = p \cdot \gamma_0 + p \wedge \gamma_0 = p^0 + \mathbf{p}$$

where p⁰ is a scalar (the temporal component) and **p** = pⁱσᵢ is a relative vector (the spatial component).

### 2.3 Bivector classification: boosts versus rotations

The six STA bivectors split into two geometrically distinct types with different algebraic properties:

- **Timelike bivectors** σᵢ = γᵢγ₀: these satisfy σᵢ² = +1 and generate **Lorentz boosts**.
- **Spacelike bivectors** γᵢγⱼ = σᵢσⱼ = Iσₖ (for cyclic ijk): these satisfy (Iσₖ)² = −1 and generate **spatial rotations**.

This classification is fundamental: the sign of a bivector's square determines whether its exponential produces trigonometric (rotation) or hyperbolic (boost) functions.

---

## Part III: Maxwell's equations in geometric algebra

### 3.1 The four equations in standard vector calculus form

For reference, Maxwell's equations in SI units with standard vector notation are:

$$\nabla \cdot \mathbf{E} = \frac{\rho}{\varepsilon_0} \qquad \text{(Gauss's law)}$$

$$\nabla \cdot \mathbf{B} = 0 \qquad \text{(Gauss's law for magnetism)}$$

$$\nabla \times \mathbf{E} = -\frac{\partial \mathbf{B}}{\partial t} \qquad \text{(Faraday's law)}$$

$$\nabla \times \mathbf{B} = \mu_0 \mathbf{J} + \mu_0\varepsilon_0 \frac{\partial \mathbf{E}}{\partial t} \qquad \text{(Ampère–Maxwell law)}$$

where c² = 1/(μ₀ε₀). These four coupled partial differential equations, involving two separate fields E and B with different transformation properties, can be unified into a single equation using geometric algebra.

### 3.2 The electromagnetic multivector in G(3)

In the Algebra of Physical Space (APS) formulation using G(3), the electric and magnetic fields combine into a single multivector:

$$\boxed{F = \mathbf{E} + Ic\mathbf{B}}$$

where **E** = Eₖeₖ is a **vector** (grade 1) representing the electric field, and Ic**B** = cBₖ(Ieₖ) is a **bivector** (grade 2) representing the magnetic field. Explicitly:

$$F = E_1 e_1 + E_2 e_2 + E_3 e_3 + cB_1 e_{23} + cB_2 e_{31} + cB_3 e_{12}$$

using the duality relations Ie₁ = e₂₃, Ie₂ = e₃₁, Ie₃ = e₁₂. The factor of c ensures consistent dimensions. This construction echoes the classical **Riemann–Silberstein vector** F = E + icB from 1907, but here the imaginary unit i is replaced by the geometric pseudoscalar I, giving it concrete geometric meaning as an oriented volume element.

### 3.3 The single Maxwell equation in G(3)

Define the spatial vector derivative ∇ = eₖ∂ₖ and the time derivative ∂₀ = (1/c)∂/∂t. The complete spacetime-aware operator in G(3) is (∂₀ + ∇). Maxwell's four equations condense into:

$$\boxed{\left(\frac{1}{c}\frac{\partial}{\partial t} + \nabla\right)\!F = \frac{\rho}{\varepsilon_0} - \frac{\mathbf{J}}{\varepsilon_0 c}}$$

The right-hand side has a **scalar part** ρ/ε₀ (grade 0) and a **vector part** −J/(ε₀c) (grade 1). The left-hand side, when expanded, produces components at all four grades. Setting each grade equal on both sides recovers all four Maxwell equations.

### 3.4 Grade decomposition recovering all four Maxwell equations

Expanding the left-hand side (∂₀ + ∇)(E + IcB) by distributing:

$$\underbrace{\frac{1}{c}\frac{\partial \mathbf{E}}{\partial t}}_{\text{grade 1}} + \underbrace{I\frac{\partial \mathbf{B}}{\partial t}}_{\text{grade 2}} + \underbrace{\nabla \cdot \mathbf{E}}_{\text{grade 0}} + \underbrace{\nabla \wedge \mathbf{E}}_{\text{grade 2}} + \underbrace{\nabla \cdot (Ic\mathbf{B})}_{\text{grade 1}} + \underbrace{\nabla \wedge (Ic\mathbf{B})}_{\text{grade 3}}$$

The key identities for the geometric product of the vector derivative ∇ with a vector and a bivector are:

- ∇E = ∇·E + ∇∧E, where ∇·E is the divergence (grade 0) and ∇∧E = I(∇×E) is a bivector (grade 2).
- ∇(IcB) = ∇·(IcB) + ∇∧(IcB), where ∇·(IcB) = −c(∇×B) is a vector (grade 1) and ∇∧(IcB) = Ic(∇·B) is a pseudoscalar (grade 3).

Collecting by grade and equating with the right-hand side:

| Grade | LHS expression | RHS | Maxwell equation |
|-------|---------------|-----|-----------------|
| **0 (scalar)** | ∇·E | ρ/ε₀ | **Gauss's law** |
| **1 (vector)** | (1/c)∂E/∂t − c(∇×B) | −J/(ε₀c) | **Ampère–Maxwell law** |
| **2 (bivector)** | I(∇×E + ∂B/∂t) | 0 | **Faraday's law** |
| **3 (pseudoscalar)** | Ic(∇·B) | 0 | **Gauss's law for magnetism** |

The grade-1 equation (1/c)∂E/∂t − c(∇×B) = −J/(ε₀c) becomes, after multiplying by c and using μ₀ = 1/(ε₀c²): ∇×B = μ₀J + μ₀ε₀ ∂E/∂t. The grade-2 equation I(∇×E + ∂B/∂t) = 0 gives ∇×E = −∂B/∂t since I is invertible.

### 3.5 The Faraday bivector in STA

In the Spacetime Algebra, the electromagnetic field is a **pure grade-2 bivector**:

$$F = E^k \sigma_k + cB^k (I\sigma_k)$$

Expanding in the STA basis using σₖ = γₖγ₀ and Iσₖ = −γⱼγₗ (for cyclic jkl):

$$F = E_1\gamma_{10} + E_2\gamma_{20} + E_3\gamma_{30} - cB_1\gamma_{23} - cB_2\gamma_{31} - cB_3\gamma_{12}$$

The six independent components of this bivector split naturally: the three **timelike bivectors** γₖ₀ carry the electric field, and the three **spacelike bivectors** γⱼₗ carry the magnetic field. Under a change of observer (different γ₀′), the same bivector F decomposes into different E′ and B′, reproducing the frame-dependent nature of the electric and magnetic fields. The bivector F itself is **frame-independent**.

The relationship to the G(3) formulation uses the spacetime split: right-multiplying by γ₀ gives Fγ₀ = E + IcB, recovering the APS multivector.

### 3.6 Maxwell's equation in STA and its explicit derivation

The **spacetime vector derivative** is:

$$\nabla = \gamma^\mu \partial_\mu = \gamma_0 \frac{\partial}{\partial(ct)} - \gamma_1\frac{\partial}{\partial x^1} - \gamma_2\frac{\partial}{\partial x^2} - \gamma_3\frac{\partial}{\partial x^3}$$

where γ⁰ = γ₀ and γⁱ = −γᵢ. The **4-current density** is the spacetime vector:

$$J = c\rho\,\gamma_0 + J^1\gamma_1 + J^2\gamma_2 + J^3\gamma_3$$

All four Maxwell equations are encoded in the single STA equation:

$$\boxed{\nabla F = \frac{J}{\varepsilon_0 c}}$$

Since ∇ is grade-1 and F is grade-2, their geometric product produces:

$$\nabla F = \underbrace{\nabla \cdot F}_{\text{grade 1 (vector)}} + \underbrace{\nabla \wedge F}_{\text{grade 3 (trivector)}}$$

The **sourced Maxwell equations** come from the vector part: ∇·F = J/(ε₀c). This single vector equation encodes both Gauss's law (the γ₀ component gives ∇·E = ρ/ε₀) and the Ampère–Maxwell law (the γₖ components give ∇×B = μ₀J + μ₀ε₀ ∂E/∂t).

The **source-free Maxwell equations** come from the trivector part: ∇∧F = 0. This encodes both Gauss's law for magnetism (the γ₁₂₃ component gives ∇·B = 0) and Faraday's law (the γ₀ⱼₖ components give ∇×E = −∂B/∂t).

In vacuum (J = 0), the equation simplifies to **∇F = 0**, and the separation ∇·F = 0 and ∇∧F = 0 shows the source-free field satisfies both sets of equations simultaneously.

### 3.7 Electromagnetic duality

The **duality rotation** F → Fe^(Iθ) for real parameter θ continuously transforms between electric and magnetic content. For the discrete duality θ = π/2:

$$F \to FI = (E + IcB)I = EI + I^2 cB = -cB + IE$$

This exchanges E ↔ −cB and cB ↔ E, the classical electromagnetic duality. The vacuum Maxwell equation ∇F = 0 is **invariant** under this rotation since I commutes with the bivector ∇F:

$$\nabla(Fe^{I\theta}) = (\nabla F)e^{I\theta} = 0$$

This duality symmetry is broken by the presence of electric sources. It would be restored only if magnetic monopoles existed, replacing J with a complex source j = j_e + Ij_m.

The **Lorentz invariants** of the field emerge from the square of F:

$$F^2 = (|\mathbf{E}|^2 - c^2|\mathbf{B}|^2) + 2cI(\mathbf{E}\cdot\mathbf{B})$$

The scalar part |E|² − c²|B|² and the pseudoscalar part 2c(E·B) are both Lorentz invariant.

---

## Part IV: Potentials, gauge theory, and the wave equation

### 4.1 The electromagnetic 4-potential and F = ∇∧A

The electromagnetic 4-potential is a spacetime vector (grade-1 element in STA):

$$A = \frac{\phi}{c}\gamma_0 + A^1\gamma_1 + A^2\gamma_2 + A^3\gamma_3$$

where φ is the scalar potential and Aⁱ are the magnetic vector potential components. The field bivector is obtained as the **exterior derivative** of the potential:

$$\boxed{F = \nabla \wedge A}$$

This definition automatically satisfies the source-free Maxwell equations, since the outer product of the derivative operator with itself vanishes by the symmetry of partial derivatives:

$$\nabla \wedge F = \nabla \wedge (\nabla \wedge A) = 0$$

This identity encodes ∇·B = 0 and ∇×E = −∂B/∂t with no further conditions required.

### 4.2 Gauge freedom and the Lorenz condition

The geometric product of ∇ with A decomposes as:

$$\nabla A = \nabla \cdot A + \nabla \wedge A = (\nabla \cdot A) + F$$

The scalar quantity ∇·A is **gauge-dependent**: the transformation A → A + ∇χ for any scalar function χ leaves F = ∇∧A unchanged (since ∇∧∇χ = 0) but shifts ∇·A → ∇·A + ∇²χ. The standard gauge choices are:

$$\text{Lorenz gauge:} \quad \nabla \cdot A = 0 \qquad \text{(}=\partial_\mu A^\mu = 0\text{)}$$

$$\text{Coulomb gauge:} \quad \nabla_{\text{spatial}} \cdot \mathbf{A} = 0$$

In the **Lorenz gauge**, the geometric product simplifies beautifully to F = ∇A (the full geometric product, not just the wedge part).

### 4.3 The wave equation

Substituting F = ∇∧A = ∇A − (∇·A) into Maxwell's equation ∇F = J/(ε₀c):

$$\nabla(\nabla A) - \nabla(\nabla \cdot A) = \frac{J}{\varepsilon_0 c}$$

Since ∇(∇A) = ∇²A (the d'Alembertian), imposing the Lorenz gauge ∇·A = 0 gives:

$$\boxed{\nabla^2 A = \square A = \frac{J}{\varepsilon_0 c}}$$

where ∇² = ∇·∇ = □ = ∂²/(c²∂t²) − ∂²/∂x² − ∂²/∂y² − ∂²/∂z² is the **d'Alembertian** (wave operator). This is the covariant wave equation for the 4-potential, equivalent to the pair of scalar equations □φ = ρ/ε₀ and □A = μ₀J in component form.

---

## Part V: Advanced topics

### 5.1 The electromagnetic stress-energy tensor

In STA, the stress-energy tensor is expressed as a **vector-valued linear function** of a vector argument n, rather than as a rank-2 tensor with indices:

$$\boxed{T(n) = -\frac{\varepsilon_0}{2}\,F\,n\,F = \frac{\varepsilon_0}{2}\,F\,n\,\tilde{F}}$$

The second equality uses the fact that for any bivector F, the reversion F̃ = −F (since reversion negates grade-2 elements). The function T(n) maps a spacetime vector n to a spacetime vector T(n), encoding energy density, momentum density, and stress.

Evaluating for specific arguments in the γ₀ frame:

- **Energy density** (from T⁰⁰): u = ⟨T(γ₀)γ₀⟩₀ = (ε₀/2)(E² + c²B²) = (1/2)(ε₀E² + B²/μ₀)
- **Poynting vector** (from T⁰ᵢ): S/c extracts from the σᵢ components of T(γ₀), giving **S** = (1/μ₀)E×B
- **Maxwell stress tensor** (from Tⁱʲ): σᵢⱼ = ε₀EᵢEⱼ + (1/μ₀)BᵢBⱼ − ½(ε₀E² + B²/μ₀)δᵢⱼ

The stress-energy tensor is **traceless** (T^μ_μ = 0), reflecting the conformal symmetry of classical electromagnetism. Conservation of energy-momentum is expressed as ∂_μ T^(μν) = F^(νλ)J_λ, which in STA becomes ∇·T(n) = (F·J)·n for the force density exerted on charges.

### 5.2 Plane wave solutions in GA notation

For a **linearly polarized monochromatic plane wave** propagating along e₃ with E polarized along e₁:

$$\mathbf{E} = E_0\cos(kz - \omega t)\,e_1, \qquad \mathbf{B} = \frac{E_0}{c}\cos(kz - \omega t)\,e_2$$

The GA field multivector is:

$$F = E_0\cos(kz - \omega t)\,(e_1 - e_{13})$$

where e₁₃ = e₁e₃ is a bivector. The factor (e₁ − e₁₃) = e₁(1 − e₃) encodes both the electric polarization direction and the magnetic field plane. This can be written more compactly as F = E₀ cos(kz − ωt) · e₁(1 − e₃).

In STA, the plane wave uses the **null wave vector** k = (ω/c)γ₀ + kⁱγᵢ satisfying k² = 0 (giving the dispersion relation ω = c|k|). The field bivector takes the form:

$$F = f_0\,e^{I\Phi}, \qquad \Phi = k \cdot x = \omega t - \mathbf{k}\cdot\mathbf{r}$$

where f₀ is a constant bivector amplitude. The factor e^(IΦ) performs a **duality rotation** that oscillates between electric and magnetic content.

**Polarization states** map naturally onto duality rotations. Linear polarization corresponds to a fixed bivector direction modulated by cos(Φ). Circular polarization arises from a π/4 duality rotation: F = f₀ exp(±Iπ/4) exp(IΦ), producing a 90° phase shift between E and B that generates helicity.

### 5.3 Lorentz transformations as rotors in STA

Any proper orthochronous Lorentz transformation of a spacetime vector a is:

$$a' = R\,a\,\tilde{R}$$

where R is an even-grade multivector (rotor) satisfying RR̃ = 1. The six-parameter Lorentz group is generated by six independent bivectors.

**Spatial rotation** by angle θ about axis n̂ uses a spacelike bivector (which squares to −1):

$$R_{\text{rot}} = e^{-I\sigma_{\hat{n}}\,\theta/2} = \cos(\theta/2) - I\sigma_{\hat{n}}\sin(\theta/2)$$

where Iσ_n̂ is the bivector dual to n̂ in the spatial subalgebra. For rotation about σ₃: R = exp(−Iσ₃ θ/2) = cos(θ/2) − Iσ₃ sin(θ/2), using the fact that (Iσ₃)² = −1.

**Lorentz boost** with rapidity α in direction n̂ uses a timelike bivector (which squares to +1):

$$R_{\text{boost}} = e^{-\sigma_{\hat{n}}\,\alpha/2} = \cosh(\alpha/2) - \sigma_{\hat{n}}\sinh(\alpha/2)$$

where tanh α = v/c. The hyperbolic functions appear because σ_n̂² = +1.

The **electromagnetic field transforms** under a Lorentz boost L as F′ = LFL̃. Expanding for a boost along σ₁ with rapidity α yields the standard transformation rules:

$$E'_\parallel = E_\parallel, \qquad B'_\parallel = B_\parallel$$
$$E'_\perp = \gamma(E_\perp + \mathbf{v}\times\mathbf{B}), \qquad B'_\perp = \gamma\!\left(B_\perp - \frac{\mathbf{v}}{c^2}\times\mathbf{E}\right)$$

where γ = cosh α. The GA derivation requires only expanding the sandwich product and applying the σᵢ commutation rules, far more economical than the index-laden tensor approach.

### 5.4 Spinors as even multivectors

In STA, a **Dirac spinor** is represented as an even-grade multivector (scalar + bivector + pseudoscalar), with the canonical Hestenes decomposition:

$$\psi = \rho^{1/2}\,e^{I\beta/2}\,R$$

where **ρ** is a positive scalar related to the probability density, **β** is the Yvon-Takabayasi angle (0 ≤ β ≤ π), and **R** is a rotor (RR̃ = 1) encoding the local Lorentz frame. This decomposition gives **8 real degrees of freedom**, matching the 4 complex components of a standard Dirac column spinor.

The **Dirac equation** in STA (the Hestenes form) is:

$$\nabla\psi\,I\sigma_3 - eA\psi = m\psi\gamma_0$$

where the factor Iσ₃ = γ₂γ₁ plays the role of the imaginary unit i of quantum mechanics, now given geometric meaning as the **spin plane** bivector. The physical observables extract directly from ψ:

- **Probability current**: J = ψγ₀ψ̃ (a conserved timelike vector)
- **Spin bivector**: S = (ℏ/2)ψσ₃ψ̃

The correspondence between column spinors and even multivectors maps the abstract Hilbert space formalism onto concrete geometric objects with direct physical interpretation.

### 5.5 How GA compares to differential forms

Both geometric algebra and the calculus of differential forms provide coordinate-free frameworks for electromagnetism, but they differ in fundamental ways.

In **differential forms**, the electromagnetic field is a 2-form F = ½F_μν dx^μ ∧ dx^ν, and Maxwell's equations require **two separate equations**:

$$dF = 0 \quad \text{(Bianchi identity)}, \qquad d{\star}F = {\star}J \quad \text{(dynamical equation)}$$

where d is the exterior derivative and ⋆ is the Hodge star operator. In **geometric algebra**, these unify into the single equation ∇F = J/(ε₀c), because the geometric product automatically produces both the inner product (which yields the sourced equations) and the outer product (which yields the source-free equations).

The core structural difference is the **geometric product** itself. Differential forms possess only the wedge product, which is not invertible. The geometric product ab = a·b + a∧b is invertible for nonzero elements, enabling division, Green's function methods, and direct algebraic manipulation that forms cannot support. The **Hodge star** ⋆ in forms, which requires a metric and orientation, corresponds to simple multiplication by the pseudoscalar I in GA — a purely algebraic operation.

For **rotations and Lorentz transformations**, GA provides built-in rotors (R = e^(−Bθ/2)) with the sandwich product v′ = RvR̃, requiring no external Lie group machinery. Forms need separate constructions for this purpose. For **spinors**, GA accommodates them naturally as even-grade multivectors, whereas differential forms require additional bundle structures.

Differential forms hold advantages in **pure mathematics**: the exterior derivative needs no metric (only differentiable structure), making forms natural on general manifolds. Stokes' theorem ∫_∂M ω = ∫_M dω and de Rham cohomology connect directly to topology. Forms also enjoy wider adoption in general relativity and gauge theory literature.

The comparison reduces to a tradeoff: GA provides a richer algebraic structure that unifies more physics into fewer equations, while differential forms provide a more minimal framework with deeper connections to topology and manifold theory.

---

## Part VI: Worked examples with full derivations

### 6.1 Deriving Gauss's law from the single GA Maxwell equation

**Goal**: Extract ∇·E = ρ/ε₀ from (1/c ∂_t + ∇)(E + IcB) = ρ/ε₀ − J/(ε₀c).

**Step 1.** Expand the left-hand side by distribution:

$$(1/c\,\partial_t + \nabla)(E + IcB) = \frac{1}{c}\partial_t E + I\partial_t B + \nabla E + \nabla(IcB)$$

**Step 2.** Expand ∇E using the geometric product of two vectors:

$$\nabla E = (e_k \partial_k)(E_j e_j) = \sum_{k,j}(\partial_k E_j)\,e_k e_j$$

Separate diagonal (k = j) and off-diagonal (k ≠ j) terms using eₖeⱼ = δₖⱼ + eₖ∧eⱼ:

$$\nabla E = \sum_k (\partial_k E_k)\underbrace{e_k e_k}_{=1} + \sum_{k\neq j}(\partial_k E_j)\underbrace{e_k e_j}_{=e_{kj}}$$

$$= \underbrace{(\partial_1 E_1 + \partial_2 E_2 + \partial_3 E_3)}_{\text{grade 0: } \nabla\cdot E} + \underbrace{\sum_{k\neq j}(\partial_k E_j)\,e_{kj}}_{\text{grade 2: } \nabla\wedge E}$$

**Step 3.** The grade-0 part of the entire left-hand side comes only from ∇·E (the terms (1/c)∂_tE, I∂_tB, and ∇(IcB) contribute no scalars). Therefore the grade-0 equation is:

$$\nabla \cdot E = \frac{\rho}{\varepsilon_0}$$

**This is Gauss's law.** ∎

### 6.2 Deriving Faraday's law from the single GA Maxwell equation

**Goal**: Extract ∇×E = −∂B/∂t from the grade-2 part.

**Step 1.** Identify all grade-2 contributions from the left-hand side:

- From (1/c)∂_tE: this is a vector (grade 1), contributes nothing to grade 2.
- From I∂_tB: since B is a vector and I maps vectors to bivectors, this is **I(∂B/∂t)**, a bivector (grade 2).
- From ∇E: the grade-2 part is ∇∧E = I(∇×E), a bivector.
- From ∇(IcB): expanding the product of a vector with a bivector, the grade-1 part is ∇·(IcB) and the grade-3 part is ∇∧(IcB). Neither contributes to grade 2.

**Step 2.** Collect the grade-2 terms:

$$\langle \text{LHS}\rangle_2 = I(\nabla \times E) + I\frac{\partial B}{\partial t} = I\!\left(\nabla \times E + \frac{\partial B}{\partial t}\right)$$

**Step 3.** The right-hand side ρ/ε₀ − J/(ε₀c) contains only grades 0 and 1, so the grade-2 equation is:

$$I\!\left(\nabla \times E + \frac{\partial B}{\partial t}\right) = 0$$

**Step 4.** Since I is invertible (I⁻¹ = −I because I² = −1), multiply both sides by I⁻¹:

$$\nabla \times E + \frac{\partial B}{\partial t} = 0 \quad \Longrightarrow \quad \nabla \times E = -\frac{\partial B}{\partial t}$$

**This is Faraday's law.** ∎

**Note**: The remaining two equations follow identically. The grade-1 equation gives (1/c)∂E/∂t − c(∇×B) = −J/(ε₀c), which simplifies to the Ampère–Maxwell law. The grade-3 equation gives Ic(∇·B) = 0, which (since Ic ≠ 0) yields ∇·B = 0.

### 6.3 Expressing a plane electromagnetic wave in GA and verifying Maxwell's equation

**Setup**: A linearly polarized plane wave propagating along e₃ with E along e₁:

$$E = E_0 \cos(kz - \omega t)\,e_1, \qquad B = \frac{E_0}{c}\cos(kz - \omega t)\,e_2$$

**Step 1. Construct the field multivector:**

$$cB = E_0\cos(kz-\omega t)\,e_2$$

$$IcB = E_0\cos(kz-\omega t)\,Ie_2 = E_0\cos(kz-\omega t)\,e_{31}$$

where Ie₂ = e₁₂₃ · e₂ = e₃₁ (verified: e₁e₂e₃e₂ = −e₁e₃ = e₃e₁ = e₃₁).

Therefore:

$$F = E_0\cos(kz - \omega t)\,(e_1 + e_{31})$$

Note that e₃₁ = e₃e₁ = −e₁e₃ = −e₁₃, so we can also write F = E₀ cos(kz − ωt)(e₁ − e₁₃).

**Step 2. Verify the source-free equation (1/c ∂_t + ∇)F = 0:**

Let ξ = kz − ωt and f(ξ) = E₀ cos ξ, so f′(ξ) = −E₀ sin ξ.

**Time derivative**: (1/c)∂_t F = (1/c)(−ω)f′(ξ) is incorrect — let me redo. Actually f(ξ) = E₀cos(ξ), so ∂f/∂t = −E₀sin(ξ)·(−ω) = ωE₀sin(ξ). Wait — ∂ξ/∂t = −ω, so ∂f/∂t = f′(ξ)·(−ω). And f′(ξ) = −E₀sinξ. So ∂f/∂t = E₀ω sinξ.

Let me use a cleaner approach. Write F = f(ξ)(e₁ + e₃₁) where ξ = kz − ωt.

$$(1/c)\,\partial_t F = \frac{1}{c}\frac{\partial f}{\partial t}(e_1 + e_{31}) = \frac{-\omega}{c}f'(\xi)(e_1 + e_{31}) \cdot \frac{1}{f'} = \frac{1}{c}(-\omega)f'(\xi)(e_1 + e_{31})$$

Wait, let me just be explicit. We have ∂F/∂t = (df/dξ)(∂ξ/∂t)(e₁ + e₃₁) = f′(ξ)(−ω)(e₁ + e₃₁).

So **(1/c)∂_tF = −(ω/c)f′(ξ)(e₁ + e₃₁) = −kf′(ξ)(e₁ + e₃₁)** using ω = ck.

**Spatial derivative**: Since F depends only on z, ∇F = e₃∂₃F = e₃ · kf′(ξ)(e₁ + e₃₁).

Now compute the products:

- e₃e₁ = −e₁e₃ = −e₁₃ = e₃₁  (a bivector)
- e₃e₃₁ = e₃(e₃e₁) = (e₃²)e₁ = e₁  (a vector)

So e₃(e₁ + e₃₁) = e₃₁ + e₁ = (e₁ + e₃₁).

Therefore: **∇F = kf′(ξ)(e₁ + e₃₁)**.

**Step 3. Sum:**

$$(1/c)\,\partial_t F + \nabla F = -kf'(\xi)(e_1 + e_{31}) + kf'(\xi)(e_1 + e_{31}) = \mathbf{0} \quad \checkmark$$

The cancellation occurs because e₃ acting on (e₁ + e₃₁) returns (e₁ + e₃₁) itself — an eigenvalue-1 property reflecting the self-reinforcing nature of electromagnetic wave propagation. ∎

### 6.4 Rotation of e₁ by angle θ around the e₃ axis using a rotor

**Step 1. Construct the rotor.** The rotation plane is e₁e₂, so the unit bivector is B̂ = e₁₂ with e₁₂² = −1:

$$R = e^{-e_{12}\theta/2} = \cos(\theta/2) - e_{12}\sin(\theta/2)$$

Write c ≡ cos(θ/2) and s ≡ sin(θ/2) for brevity.

**Step 2. Construct the reverse:** R̃ = cos(θ/2) + e₁₂ sin(θ/2) = c + e₁₂ s.

**Verify normalization**: RR̃ = (c − e₁₂s)(c + e₁₂s) = c² − e₁₂²s² = c² + s² = 1. ✓

**Step 3. Compute Re₁:**

$$Re_1 = (c - e_{12}s)e_1 = ce_1 - se_{12}e_1$$

Evaluate e₁₂e₁ = (e₁e₂)e₁ = e₁(e₂e₁) = e₁(−e₁e₂) = −e₁²e₂ = **−e₂**.

$$Re_1 = ce_1 + se_2$$

**Step 4. Compute (Re₁)R̃:**

$$(ce_1 + se_2)(c + e_{12}s)$$

Expand all four terms:

- ce₁ · c = c²e₁
- ce₁ · e₁₂s = cs · e₁e₁₂ = cs · (e₁e₁)e₂ = cs · e₂ = **cse₂**
- se₂ · c = cse₂ = **cse₂**
- se₂ · e₁₂s = s² · e₂e₁₂ = s² · (e₂e₁)e₂ = s² · (−e₁)e₂² = **−s²e₁**

**Step 5. Collect terms:**

$$v' = (c^2 - s^2)e_1 + 2cs\,e_2$$

**Step 6. Apply double-angle identities:**

$$v' = \cos\theta\,e_1 + \sin\theta\,e_2$$

This is the vector e₁ rotated counterclockwise by angle θ in the e₁e₂ plane. ∎

**Verification**: At θ = π/2, v′ = e₂ ✓. At θ = π, v′ = −e₁ ✓. At θ = 0, v′ = e₁ ✓.

### 6.5 Reflection of a vector in a plane

**Setup**: Reflect v = e₁ + 2e₂ in the plane perpendicular to n = e₁ (the yz-plane).

**Formula**: v′ = −nvn for unit n (negates the component along n, preserves perpendicular components).

**Step 1. Compute vn = (e₁ + 2e₂)e₁:**

$$vn = e_1 e_1 + 2e_2 e_1 = 1 + 2(-e_{12}) = 1 - 2e_{12}$$

**Step 2. Compute n(vn) = e₁(1 − 2e₁₂):**

$$e_1(1 - 2e_{12}) = e_1 - 2e_1 e_{12} = e_1 - 2(e_1 e_1)e_2 = e_1 - 2e_2$$

**Step 3. Apply the minus sign:**

$$v' = -(e_1 - 2e_2) = -e_1 + 2e_2$$

The e₁ component flipped sign (1 → −1) and the e₂ component is preserved (2 → 2), exactly as expected for reflection through the yz-plane. ∎

---

## Conclusion: why geometric algebra matters for electromagnetism

The reformulation of Maxwell's equations in geometric algebra is not merely notational convenience — it reveals structural insights invisible in the vector calculus formulation. The unification of E and B into a single bivector F exposes electromagnetic duality as multiplication by the pseudoscalar I, frames Lorentz invariants as the scalar and pseudoscalar parts of F², and reduces all four Maxwell equations to the single algebraic statement ∇F = J/(ε₀c). The grade decomposition of this equation provides a systematic, mechanical procedure for recovering individual field equations, replacing ad hoc vector identities with a uniform algebraic framework.

The rotor formalism eliminates the artificial distinction between rotations and boosts: both are exponentials of bivectors, differing only in whether the bivector squares to −1 or +1. The sandwich product v′ = RvR̃ applies uniformly to vectors, bivectors, and spinors, replacing the zoo of transformation rules (rotation matrices, Lorentz transformation matrices, spinor representations) with a single operation. The natural accommodation of spinors as even-grade multivectors, with the Dirac equation taking the form ∇ψIσ₃ − eAψ = mψγ₀, gives geometric meaning to the imaginary unit of quantum mechanics as the spin-plane bivector.

For practical computation, GA offers the invertibility of the geometric product (enabling algebraic division by vectors), the direct construction of Green's functions for the first-order operator ∇, and the ability to write gauge theory compactly as F = ∇∧A with the wave equation □A = J. The cost is learning a new algebraic language, but the payoff is a unified, coordinate-free framework in which classical electromagnetism, special relativity, and quantum spinor theory all speak the same mathematical language.