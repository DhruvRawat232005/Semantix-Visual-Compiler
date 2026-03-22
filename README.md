# Semantix — Visual Language Analyzer

Semantix is a visual compiler-like system for an English-like programming language. It demonstrates key compiler design phases including lexical analysis, syntax analysis, and Abstract Syntax Tree (AST) generation, with an interactive frontend for visualization.

---

## Features

- Custom English-like programming language
- Lexical Analysis using Flex (WinFlexBison)
- Recursive Descent Parser implemented in C
- Abstract Syntax Tree (AST) generation
- Syntax error detection
- Interactive frontend using Streamlit
- Visual representation of compiler phases

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
<img width="1909" height="808" alt="Screenshot 2026-03-22 125242" src="https://github.com/user-attachments/assets/f49f30b3-f66a-48d0-a431-0e69600ce697" />

### Tokens
<img width="1843" height="775" alt="Screenshot 2026-03-22 125253" src="https://github.com/user-attachments/assets/339a12d0-d614-44d0-a02b-a4f59ea420fc" />

### Abstract Syntax Tree Construction
<img width="1038" height="792" alt="Screenshot 2026-03-22 125302" src="https://github.com/user-attachments/assets/29117b89-c8dd-4398-ad82-99bad7cef7a0" />

---

## Working 

User Input
   ↓
Lexical Analysis (Flex)
   ↓
Token Stream
   ↓
Recursive Descent Parser
   ↓
AST Generation
   ↓
Frontend Visualization
