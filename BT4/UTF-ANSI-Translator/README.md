# UTF-ANSI Translator

Tool for converting between UTF-8 and ANSI encodings, with Vietnamese diacritic restoration.

## Features

- UTF-8 to ANSI conversion: Removes diacritics from Vietnamese text
- ANSI to UTF-8 conversion: Restores diacritics to Vietnamese text using machine learning model

## Setup

1. Install Python 3.8 or newer
2. Install required packages:
   ```
   cd Model
   pip install -r requirements.txt
   cd ../UnA
   pip install -r requirements.txt
   ```

## Running the application

The application consists of two services:

1. Model Service - Handles diacritic restoration
2. UnA - Web interface for text conversion

### Starting the services

The easiest way to start the services is to use the batch files:

1. First, start the Model service:
   ```
   start_model_service.bat
   ```

2. Then, start the UnA web interface:
   ```
   start_translator.bat
   ```

The web interface will automatically open in your browser at http://localhost:5000.

## Usage

1. Go to http://localhost:5000 in your browser
2. Choose conversion direction (UTF-8 to ANSI or ANSI to UTF-8)
3. Enter text or upload a file
4. Click "Convert"
5. Download or copy the converted text

## Technical Details

- The Model service runs on port 5001
- The UnA web interface runs on port 5000
- The Model service must be running for ANSI to UTF-8 conversion with diacritic restoration to work 