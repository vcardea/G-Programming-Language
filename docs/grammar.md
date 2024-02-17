$$
\begin{align}

    [\text{prog}] &\to [\text{statement}]\text{* }
    \text{EOF}
    \\

    % [\text{block}] &\to
    % \text{\text{\{} statement* \text{\}}}
    % \\

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
        \text{User\_Identifier = [expr]}
    \\

    [\text{expr}] &\to
    \begin{cases}
        [\text{comparison\_expr}]
        \\
        [\text{conditional\_expr}]
        \\
        [\text{logical\_expr}]
        \\
        [\text{addSubExpr}]
        \\
        [\text{mulDivExpr}]
        \\
        [\text{term}]
        \\
    \end{cases}
    \\

    [\text{comparison\_expr}] &\to
    \begin{cases}
        [\text{expr}] \text{ == } [\text{expr}]
        \\
        [\text{expr}] \text{ != } [\text{expr}]
        \\
        [\text{expr}] \text{ >= } [\text{expr}]
        \\
        [\text{expr}] \text{ <= } [\text{expr}]
        \\
        [\text{expr}] \text{ > } [\text{expr}]
        \\
        [\text{expr}] \text{ < } [\text{expr}]
        \\
    \end{cases}
    \\

    [\text{conditional\_expr}] &\to
    \begin{cases}
        [\text{expr}] \text{ \&\& } [\text{expr}]
        \\
        [\text{expr}] \text{ || } [\text{expr}]
        \\
    \end{cases}
    \\

    [\text{logical\_expr}] &\to
    \begin{cases}
        [\text{expr}] \text{ \& } [\text{expr}]
        \\
        [\text{expr}] \text{ | } [\text{expr}]
        \\
        [\text{expr}] \text{ \^ } [\text{expr}]
        \\
    \end{cases}
    \\

    [\text{addSubExpr}] &\to
    [\text{expr}] [\text{addSubModOp}] [\text{expr}]
    \\

    [\text{mulDivExpr}] &\to
    [\text{term}] [\text{MulDivOp}] [\text{term}]
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
        \text{Number}
        \\
        \text{Char}
        \\
        \text{true}
        \\
        \text{false}
        \\
    \end{cases}
    \\

    [\text{addSubModOp}] &\to
    \text{+} \, | \, \text{-} \, | \, \text{\%}
    \, | \, \text{++} \, | \, \text{-- --}
    \\
    
    [\text{MulDivOp}] &\to
    \text{*} \, | \, \text{/}
    \\

\end{align}
$$
