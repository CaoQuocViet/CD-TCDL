@echo off
echo Starting Model service...
cd Model
python -m venv venv
venv\Scripts\activate.bat
pip install -r requirements.txt
python model_service.py
pause 