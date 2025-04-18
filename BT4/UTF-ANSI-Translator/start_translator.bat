@echo off
echo Starting UTF-ANSI Translator...
cd UnA
python -m venv venv
venv\Scripts\activate.bat
pip install -r requirements.txt
python runserver.py
pause 