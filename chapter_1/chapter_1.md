# Chapter 1: Motion of a Charged Particle in an Electromagnetic Field

Our goal in this chapter is to derive the equation of motion for a charged particle interacting with electric and magnetic fields. We will begin with the familiar non-relativistic result, then show how it emerges naturally — and inevitably — from a relativistic Lagrangian built on four-vectors and the metric tensor. Along the way we will meet the electromagnetic field tensor $F_{\mu\nu}$, which packages $\vec{E}$ and $\vec{B}$ into a single covariant object, and we will recover the Lorentz force law as its physical consequence.

---

## 1.1 The Non-Relativistic Starting Point

Consider a point particle of rest mass $m_0$ and electric charge $q$ moving through space in the presence of an electric field $\vec{E}$ and a magnetic field $\vec{B}$. From experiment we know that the force on such a particle is

$$
\vec{F} = q\vec{E} + q\vec{V} \times \vec{B},
$$

the **Lorentz force**. In the non-relativistic limit, where $|\vec{V}| \ll c$, Newton's second law gives the equation of motion directly:

$$
m_0 \frac{d\vec{V}}{dt} = q\vec{E} + q\vec{V} \times \vec{B}.
$$

This expression is experimentally verified and conceptually straightforward: the electric field accelerates the particle along its direction, while the magnetic field deflects the particle perpendicular to its velocity without changing its speed. Our task now is to show that this result is not merely an empirical rule but follows from a variational principle — and that the same principle extends seamlessly to the relativistic regime.

---

## 1.2 Four-Vectors and the Minkowski Metric

To formulate the problem relativistically we promote the three spatial coordinates to a **four-vector**:

$$
X^\mu = (X^0,\, X^1,\, X^2,\, X^3), \qquad X^0 = ct.
$$

The derivative with respect to coordinate time is

$$
\dot{X}^\mu \equiv \frac{dX^\mu}{dt}, \qquad \text{so that} \quad \dot{X}^0 = c.
$$

Distances in Minkowski spacetime are measured with the **metric tensor**

$$
\eta_{\mu\nu} = \text{diag}(+1,\,-1,\,-1,\,-1) = \begin{pmatrix} 1 & 0 & 0 & 0 \\ 0 & -1 & 0 & 0 \\ 0 & 0 & -1 & 0 \\ 0 & 0 & 0 & -1 \end{pmatrix}.
$$

We adopt the $(+,-,-,-)$ signature throughout. (The familiar Euclidean metric $\delta_{ij}$ of three-dimensional space sits inside $\eta_{\mu\nu}$ with opposite sign on the spatial block.)

### Index gymnastics

The metric lowers an index:

$$
\dot{X}_\mu = \eta_{\mu\nu}\,\dot{X}^\nu.
$$

The Lorentz-invariant contraction of the four-velocity with itself is then

$$
\dot{X}^\mu\,\eta_{\mu\nu}\,\dot{X}^\nu = (\dot{X}^0)^2 - |\vec{V}|^2 = c^2 - |\vec{V}|^2,
$$

or equivalently,

$$
\dot{X}^\mu\,\dot{X}_\mu = c^2 - |\vec{V}|^2.
$$

This identity will be essential when we write the kinetic energy in covariant form.

---

## 1.3 Kinetic Energy in Covariant Notation

The non-relativistic kinetic energy is

$$
T = \tfrac{1}{2}\,m_0\,|\vec{V}|^2.
$$

Using the four-velocity identity above, we can rewrite this as

$$
T = \tfrac{1}{2}\,m_0\,c^2 - \tfrac{1}{2}\,m_0\,\dot{X}^\mu\,\dot{X}_\mu.
$$

The first term is a constant (the rest energy contribution) and will not affect the equations of motion. What matters is that the second term, $-\frac{1}{2}m_0\,\dot{X}^\mu\dot{X}_\mu$, is written entirely in terms of four-vectors contracted with the Minkowski metric — it is manifestly Lorentz-covariant.

---

## 1.4 The Electromagnetic Four-Potential and the Relativistic Lagrangian

### The four-potential

To include the electromagnetic interaction we introduce the **four-potential**

$$
A_\mu = (A_0,\, \vec{A}),
$$

where $A_0$ is the scalar potential and $\vec{A}$ is the vector potential. A quick dimensional check confirms that $[A_\mu]$ has dimensions of energy $\times$ length, so the combination $qA_\mu\dot{X}^\mu/c$ has the dimensions of energy — exactly what we need for a term in the Lagrangian.

### Constructing the Lagrangian

In classical mechanics the Lagrangian takes the form $L = T - V$. Here the kinetic part is the covariant expression derived in Section 1.3, and the interaction with the electromagnetic field enters through a generalized potential:

$$
\boxed{L = \frac{1}{2}\,m_0\,c^2 \;-\; \frac{1}{2}\,m_0\,\dot{X}^\mu\,\dot{X}_\mu \;-\; q\,A_\mu\,\frac{\dot{X}^\mu}{c}.}
$$

The first term is a constant and may be dropped when deriving equations of motion. The second term encodes the kinetic energy in four-vector language. The third term couples the particle's four-velocity to the electromagnetic field through $A_\mu$. This Lagrangian is the starting point for everything that follows.

### The principle of least action

The physical trajectory of the particle is the one that extremizes the action

$$
S = \int L\,dt.
$$

Demanding $\delta S = 0$ yields the **Euler–Lagrange equations**:

$$
\frac{d}{dt}\frac{\partial L}{\partial \dot{X}^\mu} - \frac{\partial L}{\partial X^\mu} = 0.
$$

We now evaluate each term in turn.

---

## 1.5 Deriving the Equations of Motion

### Step 1: Differentiation with respect to the four-velocity

We need $\partial L / \partial \dot{X}^\alpha$. Since the four-potential $A_\mu$ depends only on the coordinates — $A_\mu = A_\mu(X^0, X^1, X^2, X^3)$ — and not on the velocities, we have $\partial A_\mu / \partial \dot{X}^\alpha = 0$. Dropping the constant $\tfrac{1}{2}m_0 c^2$, the working Lagrangian is

$$
L = -\tfrac{1}{2}\,m_0\,\dot{X}^\mu\,\dot{X}_\mu - q\,A_\mu\,\frac{\dot{X}^\mu}{c}.
$$

Differentiating with respect to $\dot{X}^\alpha$:

$$
\frac{\partial L}{\partial \dot{X}^\alpha}
= \frac{\partial}{\partial \dot{X}^\alpha}\!\left(-\tfrac{1}{2}\,m_0\,\dot{X}^\mu\,\eta_{\mu\nu}\,\dot{X}^\nu\right)
- \frac{q\,A_\mu}{c}\,\frac{\partial \dot{X}^\mu}{\partial \dot{X}^\alpha}.
$$

For the kinetic term we apply the product rule. The key identity is $\partial \dot{X}^\mu / \partial \dot{X}^\alpha = \delta^\mu_\alpha$ (the Kronecker delta). Using the symmetry of $\eta_{\mu\nu}$, the two contributions from the product rule are identical, so

$$
\frac{\partial}{\partial \dot{X}^\alpha}\!\left(-\tfrac{1}{2}\,m_0\,\dot{X}^\mu\,\eta_{\mu\nu}\,\dot{X}^\nu\right)
= -m_0\,\eta_{\alpha\nu}\,\dot{X}^\nu = -m_0\,\dot{X}_\alpha.
$$

The potential term gives simply $-qA_\alpha/c$. Combining:

$$
\boxed{\frac{\partial L}{\partial \dot{X}^\alpha} = -m_0\,\dot{X}_\alpha - \frac{q\,A_\alpha}{c}.}
$$

This quantity is the **generalized (canonical) momentum** conjugate to $X^\alpha$.

### Step 2: Differentiation with respect to the coordinates

Since the kinetic term depends only on velocities, its derivative with respect to $X^\alpha$ vanishes. Only the interaction term contributes. Introducing the shorthand $\partial_\alpha \equiv \partial / \partial X^\alpha$:

$$
\frac{\partial L}{\partial X^\alpha} = -\frac{q}{c}\,\partial_\alpha A_\mu\;\dot{X}^\mu.
$$

### Step 3: Assembling the Euler–Lagrange equation

We need the total time derivative of the generalized momentum:

$$
\frac{d}{dt}\!\left(\frac{\partial L}{\partial \dot{X}^\alpha}\right)
= -m_0\,\eta_{\alpha\nu}\,\ddot{X}^\nu - \frac{q}{c}\,\frac{dA_\alpha}{dt}.
$$

The total time derivative of $A_\alpha$ is evaluated by the chain rule:

$$
\frac{dA_\alpha}{dt} = \frac{\partial A_\alpha}{\partial X^\mu}\,\dot{X}^\mu = \partial_\mu A_\alpha\;\dot{X}^\mu.
$$

Substituting both results into the Euler–Lagrange equation $\frac{d}{dt}(\partial L/\partial\dot{X}^\alpha) - \partial L/\partial X^\alpha = 0$:

$$
-m_0\,\eta_{\alpha\nu}\,\ddot{X}^\nu
\;-\; \frac{q}{c}\,\partial_\mu A_\alpha\;\dot{X}^\mu
\;+\; \frac{q}{c}\,\partial_\alpha A_\mu\;\dot{X}^\mu = 0.
$$

Rearranging for the four-acceleration:

$$
m_0\,\ddot{X}_\alpha = \frac{q}{c}\left(\partial_\alpha A_\mu - \partial_\mu A_\alpha\right)\dot{X}^\mu.
$$

The combination of derivatives on the right-hand side is antisymmetric in $\alpha$ and $\mu$. This is no accident — it is the hallmark of a new tensor.

---

## 1.6 The Electromagnetic Field Tensor

We define the **electromagnetic field tensor** as

$$
\boxed{F_{\alpha\nu} = c\left(\partial_\alpha A_\nu - \partial_\nu A_\alpha\right).}
$$

By construction $F_{\alpha\nu}$ is antisymmetric: $F_{\alpha\nu} = -F_{\nu\alpha}$. The equation of motion then takes the elegant covariant form

$$
\boxed{m_0\,\ddot{X}_\alpha = \frac{q}{c}\,F_{\alpha\mu}\,\dot{X}^\mu.}
$$

This single tensor equation encodes all the information about how a charged particle moves in an electromagnetic field, valid in any inertial frame.

### A note on proper time

For a fully relativistic treatment one replaces coordinate-time derivatives with proper-time derivatives. The proper time $\tau$ is related to coordinate time by

$$
d\tau = \sqrt{1 - v^2/c^2}\;dt,
$$

and the four-acceleration $d^2 X^\alpha / d\tau^2$ transforms as a proper four-vector. The structure of the equation of motion remains unchanged — the field tensor $F_{\alpha\mu}$ simply contracts with the four-velocity $dX^\mu/d\tau$ instead of $\dot{X}^\mu$.

---

## 1.7 Decomposing the Field Tensor into $\vec{E}$ and $\vec{B}$

The field tensor is a $4\times 4$ antisymmetric object and therefore has six independent components. These map exactly onto the three components of $\vec{E}$ and the three components of $\vec{B}$.

### Identifying the electric field

To isolate the electric field, consider the force component with $\nu = 0$ (the time-like part). Since $\dot{X}^0 = c$, the contribution to the spatial force $F_j$ from the time-like index is

$$
\frac{q}{c}\,(\partial_j A_0 - \partial_0 A_j)\,c \cdot \frac{\dot{X}^0}{c} = q\,(\partial_j A_0 - \partial_0 A_j)\,c \cdot 1.
$$

We recognize this as the $j$-th component of the electric field:

$$
\boxed{\vec{E} = \vec{\nabla}A_0 - \frac{1}{c}\frac{\partial \vec{A}}{\partial t}.}
$$

Here $\partial_0 = (1/c)\,\partial/\partial t$, so $\partial_0 A_j = (1/c)\,\partial A_j/\partial t$.

### Identifying the magnetic field

The remaining (space-like, $\nu = i$) part of the force involves the antisymmetric spatial components $\partial_j A_i - \partial_i A_j$. To connect these to the magnetic field we use the **Levi-Civita symbol** $\varepsilon_{ijk}$, the fully antisymmetric tensor in three dimensions.

The key identity is

$$
\partial_j A_i - \partial_i A_j = \varepsilon_{jim}\,B^m \cdot c,
$$

which, after contracting with $\varepsilon^{kji}$ and using the identity $\varepsilon^{kji}\varepsilon_{jim} = 2\,\delta^k_m$, gives

$$
B^k \cdot c = \varepsilon^{kij}\,\partial_i A_j + \varepsilon^{kij}\,\partial_j A_i = 2\,\varepsilon^{kij}\,\partial_i A_j.
$$

The expression $\varepsilon^{kij}\,\partial_i A_j$ is precisely the $k$-th component of $\vec{\nabla}\times\vec{A}$, so we arrive at

$$
\boxed{\vec{B} = \frac{1}{c}\,\vec{\nabla}\times\vec{A}.}
$$

---

## 1.8 Recovery of the Lorentz Force Law

We are now in a position to reassemble the spatial components of the covariant force equation. Splitting the sum over $\nu$ into its time-like and space-like parts, the force on the $j$-th spatial component is

$$
F_j = \frac{q}{c}\,E_j \cdot c + \frac{q}{c}\,\varepsilon_{jim}\,B^m \cdot c \cdot \dot{X}^i.
$$

Canceling factors of $c$:

$$
F_j = q\,E_j + q\,\varepsilon_{jim}\,\dot{X}^i\,B^m.
$$

The second term is recognized as the $j$-th component of the cross product $\vec{V}\times\vec{B}$. In vector form:

$$
\boxed{\vec{F} = q\vec{E} + q\vec{V}\times\vec{B}.}
$$

This is the **Lorentz force law**, now derived from first principles via the relativistic Lagrangian and the electromagnetic field tensor. What began as an empirical observation in Section 1.1 has been shown to be a necessary consequence of the principle of least action applied to a covariant Lagrangian coupling a charged particle to the four-potential $A_\mu$.

---

## 1.9 Summary of Key Results

| Quantity | Symbol | Definition |
|---|---|---|
| Relativistic Lagrangian | $L$ | $\frac{1}{2}m_0 c^2 - \frac{1}{2}m_0\dot{X}^\mu\dot{X}_\mu - qA_\mu\dot{X}^\mu/c$ |
| Field tensor | $F_{\mu\nu}$ | $c(\partial_\mu A_\nu - \partial_\nu A_\mu)$ |
| Electric field | $\vec{E}$ | $\vec{\nabla}A_0 - \frac{1}{c}\frac{\partial\vec{A}}{\partial t}$ |
| Magnetic field | $\vec{B}$ | $\frac{1}{c}\vec{\nabla}\times\vec{A}$ |
| Covariant equation of motion | $m_0\ddot{X}_\alpha$ | $\frac{q}{c}F_{\alpha\mu}\dot{X}^\mu$ |
| Lorentz force | $\vec{F}$ | $q(\vec{E} + \vec{V}\times\vec{B})$ |
| Metric signature | $\eta_{\mu\nu}$ | $(+1,\,-1,\,-1,\,-1)$ |

The chain of logic in this chapter is worth internalizing:

1. **Start** with the covariant kinetic energy and the minimal coupling $qA_\mu\dot{X}^\mu/c$.
2. **Apply** the Euler–Lagrange equations to obtain a covariant equation of motion.
3. **Define** the field tensor $F_{\mu\nu}$ from the antisymmetric combination of potential derivatives.
4. **Decompose** the tensor into $\vec{E}$ and $\vec{B}$ using the Levi-Civita symbol.
5. **Recover** the Lorentz force as the three-vector content of the covariant equation.

Every step is dictated by Lorentz covariance and the variational principle — no additional assumptions are needed. In the chapters that follow we will use the field tensor to derive Maxwell's equations themselves and to explore the dynamics of electromagnetic waves.
