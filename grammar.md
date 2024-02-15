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
        [\text{comparison}]
        \\
        \text{( [expr] )}
        \\
        \text{[term] + [term]}
        \\
        \text{[term] - [term]}
        \\
        \text{[term] * [term]}
        \\
        \text{[term] / [term]}
        \\
        \text{[term] \% [term]}
        \\
    \end{cases}
    \\

    [\text{term}] &\to
    \begin{cases}
        \text{User\_Identifier}
        \\
        [\text{const\_value}]
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

    
\end{align}
$$