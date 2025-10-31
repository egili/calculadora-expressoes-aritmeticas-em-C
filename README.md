# Calculadora de expressões aritméticas em C
O propósito deste trabalho é, usando pilhas e filas, construir em C o programa de uma Calculadora de Expressões Aritméticas usando notação polonesa prefixa e pós-fixa.
<br />
O desenvolvimento baseia-se no algoritmo de pátio de manobras (Shunting yard)

---

## Funcionamento da Calculadora

### 1. Entrada da expressão (Notação infixa)
O usuário digita uma expressão aritmética tradicional, por exemplo:

10 + (2 * 3 - 4) ^ 2 / 4 + 6 * 2


### 2. Remoção de espaços desnecessários
Espaços que não estejam entre dígitos devem ser removidos. Se houver espaços entre dígitos, o programa deve emitir um erro.

Exemplo após remoção:

10+(23-4)^2/4+62

### 3. Quebra da expressão em tokens
Separar números, operadores e parênteses, armazenando-os em uma **fila de entrada**.

Fila de entrada:

10, +, (, 2, *, 3, -, 4, ), ^, 2, /, 4, +, 6, *, 2

---

## Conversão da expressão infixa para pós-fixa (RPN)

### Estruturas necessárias:
- Fila de entrada (tokens da expressão)
- Pilha de operadores
- Fila de saída (expressão pós-fixa)

### Regras:
- **Números:** vão direto para fila de saída.
- **Parênteses abertos:** empilhados.
- **Parênteses fechados:** desempilham operadores para a fila de saída até desempilhar o parêntese aberto correspondente.
- **Operadores:** ao ler um operador, desempilhar da pilha operadores de maior ou igual precedência, conforme a tabela fornecida, antes de empilhar o novo operador.

---

## Tabela de precedência e desempilhamento

A tabela usada indica com `T` (True) ou `F` (False) se o operador no topo da pilha deve ser desempilhado antes de empilhar o operador da entrada.

**Exemplo:**
- Topo da pilha: `*`, próximo operador: `+` → desempilha `*` antes de empilhar `+`.
- Topo da pilha: `^`, próximo operador: `*` → não desempilha `^` (precedência maior e associatividade à direita).

---

## Avaliação da expressão pós-fixa

Após converter para pós-fixa, usa-se uma pilha de resultados:

- Para cada número: empilhar.
- Para cada operador: desempilhar dois operandos, aplicar o operador, empilhar o resultado.
- Ao final, a pilha terá um único valor, o resultado final.

---

## Tratamento de Erros
- Expressões malformadas (ex.: parênteses sem correspondência)
- Divisão por zero
- Espaços incorretos entre dígitos

---

## Exemplo Completo

Entrada:
10 + (2 * 3 - 4) ^ 2 / 4 + 6 * 2

Fila pós-fixa:
10, 2, 3, *, 4, -, 2, ^, 4, /, +, 6, 2, *, +

Resultado final:
23





<hr/>
<h3>Desenvolvido por:</h3>

<table>
  <tr>
        <td align="center">
            <a href="https://github.com/egili">
                <img src="https://avatars.githubusercontent.com/u/79612701?v=4" width="100px;" alt="egili"/>
                <br>
                <sub>
                    <b>egili</b>
                </sub>
            </a>
        </td>
        <td align="center">
            <a href="https://github.com/Rnchx">
                <img src="https://avatars.githubusercontent.com/u/123501793?v=4" width="100px;" alt="Rnchx"/>
                <br>
                <sub>
                    <b>Rnchx</b>
                </sub>
            </a>
        </td>
    </tr>
</table>
