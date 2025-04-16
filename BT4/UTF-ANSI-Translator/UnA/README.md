# UnA - UTF-8/ANSI Converter

A simple tool for converting between UTF-8 (Vietnamese with diacritics) and ANSI (Vietnamese without diacritics).

## Features

- Convert UTF-8 encoded text (with diacritics) to ANSI (without diacritics)
- Convert ANSI encoded text (without diacritics) to UTF-8 (with diacritics)
- Web interface for easy file uploads and downloads
- Preview of conversion results

## Installation

```bash
# Clone the repository (if applicable)
# git clone https://your-repo-url.git
# cd una

# Create virtual environment
python -m venv venv

# Activate virtual environment
# On Windows:
venv\Scripts\activate
# On macOS/Linux:
# source venv/bin/activate

# Install dependencies
pip install -r requirements.txt
```

## Usage

```bash
# Run the application
python app.py
```

Then open your browser and navigate to: http://localhost:5000

## How it Works

- UTF-8 to ANSI: Removes diacritics from Vietnamese text
- ANSI to UTF-8: Restores diacritics using a trained machine learning model

## Requirements

- Python 3.8 or higher
- See requirements.txt for Python package dependencies 