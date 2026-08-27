import streamlit as st
import sqlite3
import pandas as pd

st.title("Smart Parking Dashboard")

conn = sqlite3.connect("smart_parking.db")
df = pd.read_sql_query("SELECT * FROM parking_events", conn)
conn.close()

st.dataframe(df)

if "status" in df.columns:
    occupied = (df["status"] == "occupied").sum()
    free = (df["status"] == "free").sum()

    st.metric("Occupied", occupied)
    st.metric("Free", free)