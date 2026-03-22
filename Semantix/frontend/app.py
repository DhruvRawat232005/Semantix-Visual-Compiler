import streamlit as st
import subprocess
import os
import platform
import pandas as pd
basedir=os.path.abspath(os.path.join(os.path.dirname(__file__),".."))
input=os.path.join(basedir,"input","input.txt")
output=os.path.join(basedir,"output")
exe=os.path.join(basedir,"semantix.exe" if platform.system=="Windows" else "semantix")
os.makedirs(os.path.dirname(input),exist_ok=True)
os.makedirs(output,exist_ok=True)

st.set_page_config(page_title="Semantix Compiler", layout="wide")

def load_css():
    st.markdown("""
<style>
.stApp {
    background-color: #020617;
}
.main {
    background-color: #020617;
}
section[data-testid="stSidebar"] {
    background-color: #0F172A;
}
textarea {
    background-color: #020617 !important;
    color: #E2E8F0 !important;
}
input {
    background-color: #020617 !important;
    color: white !important;
}
</style>
""", unsafe_allow_html=True)
    st.markdown("""
<div class="main-title" style="text-align:center;">
    Semantix
</div>
<div style="color:#94A3B8; font-size:16px; margin-bottom:20px; text-align:center;">
    Visual Compiler For Easy Learning<br>
</div>
""", unsafe_allow_html=True)
    st.markdown("""
<style>
.main-title {
    font-size: 40px;
    font-weight: 700;
    color: #38BDF8;
}
.section-title {
    font-size: 22px;
    font-weight: 600;
    color: #22D3EE;
}
.card {
    background-color: #1E293B;
    padding: 12px;
    border-radius: 10px;
    margin-bottom: 10px;
}
</style>
""", unsafe_allow_html=True)
load_css()

def write_ip(code):
    with open(input,"w") as f:
        f.write(code)

def run():
    try:
        res=subprocess.run(
            [exe,input],
            capture_output=True,
            text=True 
        )
        return res.stdout, res.stderr
    except FileNotFoundError:
        return "","File not found"
    except Exception as e:
        return "",str(e)

def readfile(fn):
    path=os.path.join(output,fn)
    if os.path.exists(path):
        with open(path,"r") as f:
            return f.read()
    return ""

def display_symtab():
    d=readfile("symbol_table.txt")
    r=[line.split() for line in d.split("\n") if line.split()]
    if len(r) > 1:
        df = pd.DataFrame(r[1:], columns=r[0])
        st.markdown("""
        <style>
        .stDataFrame {
            background-color: white;
            color: black;
        }
        </style>
        """, unsafe_allow_html=True)
        st.dataframe(df, use_container_width=True)
    else:
        st.code("No symbol table made yet",language="text")

st.markdown('<div class="section-title">Code Input</div>',unsafe_allow_html=True)
mess="Write Code here"
code=st.text_area("",value=mess,height=220)
runbtn=st.button("Run")
if runbtn:
    write_ip(code)
    stdout,stderr=run()
    if stderr:
        st.error(stderr)
    else:
        st.success("Compilation Done")
    if stdout:
        with st.expander("Execution Logs"):
            st.text(stdout)

st.markdown('<div class="section-title">Compiler Output</div>',unsafe_allow_html=True)
c1,c2=st.columns(2)
with c1:
    st.markdown('<div class="card"><span style="color:#38BDF8; font-size:18px;"><b>Tokens</b></span></div>', unsafe_allow_html=True)
    st.code(readfile("tokens.txt"), language="text")
    st.markdown('<div class="card"><span style="color:#38BDF8; font-size:18px;"><b>Abstract Syntax Tree</b></span></div>', unsafe_allow_html=True)
    st.code(readfile("ast.txt"), language="text")
    st.markdown('<div class="card"><span style="color:#38BDF8; font-size:18px;"><b>Symbol Table</b></span></div>', unsafe_allow_html=True)
    display_symtab()
with c2:
    st.markdown('<div class="card"><span style="color:#38BDF8; font-size:18px;"><b>Intermediate Code</b></span></div>', unsafe_allow_html=True)
    st.code(readfile("ir.txt"), language="text")
    st.markdown('<div class="card"><span style="color:#38BDF8; font-size:18px;"><b>Optimized Code</b></span></div>', unsafe_allow_html=True)
    st.code(readfile("optimized.txt"), language="text")
    st.markdown('<div class="card"><span style="color:#38BDF8; font-size:18px;"><b>Errors</b></span></div>', unsafe_allow_html=True)
    errors = readfile("errors.txt")
    if errors.strip():
        st.code(errors, language="text")
    else:
        st.code("No errors", language="text")
