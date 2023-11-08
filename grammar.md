$$
\begin{align}

    [\text{prog}] &\to [\text{stmt}]*
    \\

    [\text{stmt}] &\to
    \begin{cases}
        \text{[\text{type}] ident = [\text{expr}]};
        \\
        \text{[\text{type}] function\_definition([\text{type}] argument*) \{ [\text{stmt}]* \}}
        \\
        \text{function\_call([\text{expr}]*);}
        \\
        \text{struct s\_definition \{ [\text{stmt}]* \}}
        \\
    \end{cases}
    \\

    [\text{type}] &\to
    \begin{cases}
        \text{boolean}
        \\
        \text{int}
        \\
        \text{float}
        \\
        \text{char}
        \\
        \text{struct s\_declaration}
        \\
        \text{boolean[[\text{expr}]]}
        \\
        \text{int[[\text{expr}]]}
        \\
        \text{float[[\text{expr}]]}
        \\
        \text{char[[\text{expr}]]}
        \\
        \text{struct s\_declaration[[\text{expr}]]}
        \\
    \end{cases}
    \\

    [\text{expr}] &\to
    \begin{cases}
        [\text{term}]
        \\
        [\text{term}] + [\text{term}]
        \\
        [\text{term}] - [\text{term}]
        \\
        [\text{term}] * [\text{term}]
        \\
        [\text{term}] / [\text{term}]
        \\
        [\text{expr}] + [\text{expr}]
        \\
        [\text{expr}] - [\text{expr}]
        \\
        [\text{expr}] * [\text{expr}]
        \\
        [\text{expr}] / [\text{expr}]
        \\
        [\text{expr}] + [\text{term}]
        \\
        [\text{expr}] - [\text{term}]
        \\
        [\text{expr}] * [\text{term}]
        \\
        [\text{expr}] / [\text{term}]
        \\
        [\text{term}] + [\text{expr}]
        \\
        [\text{term}] - [\text{expr}]
        \\
        [\text{term}] * [\text{expr}]
        \\
        [\text{term}] / [\text{expr}]
        \\
    \end{cases}
    \\

    [\text{term}] &\to
    \begin{cases}
        \text{ident}
        \\
        [\text{factor}]
        \\
    \end{cases}
    \\

    [\text{factor}] &\to
    \begin{cases}
        \text{integer}
        \\
        \text{float}
        \\
    \end{cases}

\end{align}
$$