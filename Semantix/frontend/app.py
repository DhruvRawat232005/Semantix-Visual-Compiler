import streamlit as st
import subprocess
import os
import platform
import pandas as pd

basedir = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
input = os.path.join(basedir, "input", "input.txt")
output = os.path.join(basedir, "output")
exe = os.path.join(basedir, "semantix.exe" if platform.system() == "Windows" else "semantix")

os.makedirs(os.path.dirname(input), exist_ok=True)
os.makedirs(output, exist_ok=True)

st.set_page_config(page_title="Semantix Compiler", layout="wide")

def load_css():
    st.markdown("""
    <style>

    .stApp {
        background-color: #FFFFFF;
        color: #1F2937;
    }

    textarea {
        background-color: #FFFFFF !important;
        color: #1F2937 !important;
        border: 1px solid #E5E7EB !important;
    }

    .main-title {
        font-size: 42px;
        font-weight: 700;
        color: #FF6A00;
        text-align: center;
    }

    .subtitle {
        text-align: center;
        color: #6B7280;
        margin-bottom: 25px;
    }

    .section-title {
        font-size: 22px;
        font-weight: 600;
        color: #FF6A00;
        margin-top: 10px;
    }

    .card {
        background-color: #F9FAFB;
        padding: 10px;
        border-radius: 10px;
        border: 1px solid #E5E7EB;
        margin-bottom: 8px;
    }

    .stButton>button {
        background-color: #FF6A00;
        color: white;
        border-radius: 8px;
        border: none;
        font-weight: 600;
    }

    .stButton>button:hover {
        background-color: #e55d00;
    }

    </style>
    """, unsafe_allow_html=True)

    st.markdown("""
    <div class="main-title">Semantix</div>
    <div class="subtitle">
        Visual Compiler For Easy Learning
    </div>
    """, unsafe_allow_html=True)

load_css()

def write_ip(code):
    with open(input, "w") as f:
        f.write(code)

def run():
    try:
        res = subprocess.run(
            [exe, input],
            capture_output=True,
            text=True
        )
        return res.stdout, res.stderr
    except FileNotFoundError:
        return "", "Executable not found"
    except Exception as e:
        return "", str(e)

def readfile(fn):
    path = os.path.join(output, fn)
    if os.path.exists(path):
        with open(path, "r") as f:
            return f.read()
    return ""

def display_symtab():
    d = readfile("symbol_table.txt")
    r = [line.split() for line in d.split("\n") if line.split()]

    if len(r) > 1:
        df = pd.DataFrame(r[1:], columns=r[0])
        st.dataframe(df, use_container_width=True)
    else:
        st.code("No symbol table made yet", language="text")

st.markdown('<div class="section-title">Code Input</div>', unsafe_allow_html=True)

default_code = """DECLARE a AS 5
DECLARE b AS 10
SET c TO a + b * 2
PRINT c
"""

code = st.text_area("", value=default_code, height=220)

runbtn = st.button("Run Compiler")

if runbtn:
    write_ip(code)
    stdout, stderr = run()

    if stderr:
        st.error(stderr)
    else:
        st.success("Compilation Successful")

    if stdout:
        with st.expander("Execution Logs"):
            st.text(stdout)

st.markdown('<div class="section-title">Compiler Output</div>', unsafe_allow_html=True)

c1, c2 = st.columns(2)

with c1:
    st.markdown('<div class="card"><b>Tokens</b></div>', unsafe_allow_html=True)
    st.code(readfile("tokens.txt"), language="text")

    st.markdown('<div class="card"><b>Abstract Syntax Tree</b></div>', unsafe_allow_html=True)
    st.code(readfile("ast.txt"), language="text")

    st.markdown('<div class="card"><b>Symbol Table</b></div>', unsafe_allow_html=True)
    display_symtab()

with c2:
    st.markdown('<div class="card"><b>Intermediate Code</b></div>', unsafe_allow_html=True)
    st.code(readfile("ir.txt"), language="text")

    st.markdown('<div class="card"><b>Optimized Code</b></div>', unsafe_allow_html=True)
    st.code(readfile("optimized.txt"), language="text")

    st.markdown('<div class="card"><b>Errors</b></div>', unsafe_allow_html=True)
    errors = readfile("errors.txt")
    if errors.strip():
        st.code(errors, language="text")
    else:
        st.code("No errors", language="text")