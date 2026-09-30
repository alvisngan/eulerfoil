# Equations Used

## Gas Dynamics

### State Vector

$$
\overrightarrow{\omega} =
\begin{pmatrix}
    \rho \\ \rho u \\ \rho v \\ \rho E
\end{pmatrix}
=
\begin{pmatrix}
    \rho \\ m_1 \\ m_2 \\ e
\end{pmatrix}
$$

### Pressure

$$
p = (\gamma - 1) \rho \left( E - \frac{u^2 + v^2}{2} \right) \\
p = (\gamma - 1) \left( e - \frac{m_1^2 + m_2^2}{2 \rho} \right)
$$

### Flux Vector

$$
H = E + \frac{p}{\rho} = \frac{e + p}{\rho}
$$

$$
\overrightarrow{f} =
\begin{pmatrix}
    \rho u \\ \rho u^2 + p \\ \rho u v \\ \rho u H
\end{pmatrix}
=
\begin{pmatrix}
    m_1 \\ \frac{m_1^2}{\rho} + p \\ \frac{m_1 m_2}{\rho} \\ \frac{m_1 (e + p)}{\rho}
\end{pmatrix}
$$

$$
\overrightarrow{g} =
\begin{pmatrix}
    \rho v \\ \rho u v \\ \rho v^2 + p \\ \rho v H
\end{pmatrix}
=
\begin{pmatrix}
    m_2 \\ \frac{m_1 m_2}{\rho} \\ \frac{m_2^2}{\rho} + p \\ \frac{m_2 (e + p)}{\rho}
\end{pmatrix}
$$

### Speed of Sound

Ideal gas

$$
c = \sqrt{\frac{\gamma p}{\rho}}
$$
