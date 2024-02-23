$$
\begin{align}

    [\text{prog}] &\to [\text{statement}]\text{ * }
    \\

    [\text{statement}] &\to
    \begin{cases}
        [\text{declaration}]
        \\
        [\text{assignment}]
        \\
        % [\text{ifStmt}]
        % \\
        % [\text{whileStmt}]
        % \\
    \end{cases}
    \\

    [\text{declaration}] &\to
    \begin{cases}
        \text{Type\_Keyword User\_Identifier}
        \\
        % \text{Return\_Type Function\_Name}
        % \\
    \end{cases}
    \\

    [\text{assignment}] &\to
        \text{User\_Identifier '=' [expr]}
    \\

    [\text{expr}] &\to
    [\text{conditional\_expr}]
    \\

    [\text{conditional\_expr}] &\to
    [\text{expr}] [\text{conditional\_op}] [\text{expr}] \text{ | } [\text{comparison\_expr}]
    \\

    [\text{comparison\_expr}] &\to
    [\text{expr}] [\text{logical\_op}] [\text{expr}] \text{ | } [\text{logical\_expr}]
    \\

    [\text{logical\_expr}] &\to
    [\text{expr}] [\text{bitwise\_op}] [\text{expr}] \text{ | } [\text{addSubMod\_expr}]
    \\

    [\text{addSubMod\_expr}] &\to
    [\text{expr}] [\text{addSubMod\_op}] [\text{expr}] \text{ | } [\text{mulDiv\_expr}]
    \\

    [\text{mulDiv\_expr}] &\to
    [\text{expr}] [\text{mulDiv\_op}] [\text{expr}] \text{ | } [\text{term\_expr}]
    \\

    [\text{term}] &\to
    \begin{cases}
        \text{User\_Identifier}
        \\
        [\text{const\_value}]
        \\
        \text{( [expr] )}
        \\
    \end{cases}
    \\

    [\text{const\_value}] &\to
    \begin{cases}
        \text{Int\_Literal}
        \\
        \text{Float\_Literal}
        \\
        \text{Char\_Literal}
        \\
        \text{String\_Literal}
        \\
        \text{true}
        \\
        \text{false}
        \\
    \end{cases}
    \\

    [\text{comparison\_op}] &\to
    \text{ > } | \text{ < } |
    \text{ >= } | \text{ <= } |
    \text{ == } | \text{ != }
    \\

    [\text{logical\_op}] &\to
    \text{ \&\& } | \text{ || }
    \\

    [\text{bitwise\_op}] &\to
    \text{ \& } | \text{ ! } |
    \text{ \^ } | \text{ | }
    \\

    [\text{addSubMod\_op}] &\to
    \text{ + } | \text{ - } | \text{ \% } |
    \text{ ++ } | \text{ - - }
    \\
    
    [\text{mulDiv\_op}] &\to
    \text{ * } | \text{ / }
    \\

\end{align}
$$
