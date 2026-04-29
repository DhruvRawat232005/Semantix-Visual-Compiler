# Semantix — Visual Language Compiler

Semantix is a visual compiler-like system for an English-like programming language. It demonstrates key compiler design phases including lexical analysis, syntax analysis, and Abstract Syntax Tree (AST) generation, with an interactive frontend for visualization.

---

## Features

- Custom English-like programming language
- Lexical Analysis using Flex (WinFlexBison)
- Recursive Descent Parser implemented in C
- Abstract Syntax Tree (AST) generation
- Syntax error detection
- Symbol Table generation
- Intermediate Code Generation
- Code Optimization (Constant Folding Method)
- Interactive frontend using Streamlit

---

## Tech Stack

| Component        | Technology |
|----------------|----------|
| Frontend        | Python (Streamlit) |
| Backend         | C |
| Lexical Analysis| Flex (WinFlexBison) |
| Parsing         | Recursive Descent Parser |
| Visualization   | Streamlit UI |

---

## Screenshots

### Dashboard
<img width="1903" height="869" alt="Screenshot 2026-04-29 200231" src="https://github.com/user-attachments/assets/e0852b40-8db7-48dd-81f6-7a90fec14d19" />

### Tokens
<img width="873" height="755" alt="Screenshot 2026-04-29 200252" src="https://github.com/user-attachments/assets/c1207e86-222b-4035-b6f4-be76236a7c85" />

### Abstract Syntax Tree Construction
<img width="882" height="558" alt="Screenshot 2026-04-29 200304" src="https://github.com/user-attachments/assets/46e8a0a1-2338-4c5c-b9ff-2533c74eae22" />

### Symbol Table 
<img width="885" height="366" alt="Screenshot 2026-04-29 200313" src="https://github.com/user-attachments/assets/5c85d4a5-2efd-48c8-9d1e-6d57fb847920" />

### Intermediate Code Generation
<img width="858" height="370" alt="Screenshot 2026-04-29 200322" src="https://github.com/user-attachments/assets/7b23c85f-028c-4a44-8b22-aad722b9f589" />

### Optimized Code
<img width="856" height="357" alt="Screenshot 2026-04-29 200331" src="https://github.com/user-attachments/assets/fa48528c-8941-45a5-8ea0-b3f0350ce794" />

---

## Working 

User Input -> Lexical Analysis (Flex) -> Token Stream -> Recursive Descent Parser -> AST Generation -> Symbol Table generation -> Intermediate Code Generation -> Code Optimization -> Frontend Visualization
