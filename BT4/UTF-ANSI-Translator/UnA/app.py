#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
UnA - UTF-8/ANSI Converter Web Application
"""

import os
import uuid
import traceback
from flask import Flask, render_template, request, jsonify, send_from_directory, url_for

from modules.predictor import Predictor
from modules.converter import Converter
from modules.utils import read_file, get_temp_directory

# Initialize Flask app
app = Flask(__name__)

# Configure upload folder
TEMP_DIR = get_temp_directory()
app.config['TEMP_FOLDER'] = TEMP_DIR
app.config['MAX_CONTENT_LENGTH'] = 5 * 1024 * 1024  # 5MB max file size

# Initialize predictor and converter
try:
    print("Initializing predictor...")
    predictor = Predictor()
    
    # Test predictor
    if hasattr(predictor, 'model_loaded') and predictor.model_loaded:
        print("Testing predictor with sample text...")
        test_result = predictor.predict("day la mot thu nghiem")
        print(f"Test result: {test_result}")
    else:
        print("Warning: Predictor model not loaded correctly")
    
    print("Initializing converter...")
    converter = Converter(predictor=predictor)
except Exception as e:
    print(f"Error initializing predictor or converter: {e}")
    traceback.print_exc()
    # Initialize converter without predictor if there's an error
    print("Falling back to converter without predictor")
    converter = Converter()

@app.route('/')
def index():
    """Render the main page"""
    return render_template('index.html')

@app.route('/convert', methods=['POST'])
def convert():
    """Convert text between UTF-8 and ANSI"""
    try:
        # Get the conversion direction
        direction = request.form.get('direction', 'utf8_to_ansi')
        print(f"Conversion request received. Direction: {direction}")
        
        # Check if file or text input
        if 'file' in request.files and request.files['file'].filename:
            # File input
            file = request.files['file']
            print(f"Processing file: {file.filename}")
            
            # Generate unique filename
            original_filename = file.filename
            filename_base, filename_ext = os.path.splitext(original_filename)
            unique_id = str(uuid.uuid4())
            
            # Save uploaded file
            input_path = os.path.join(app.config['TEMP_FOLDER'], f"{filename_base}_{unique_id}_input{filename_ext}")
            file.save(input_path)
            print(f"File saved to: {input_path}")
            
            # Set output filename and path
            if direction == 'utf8_to_ansi':
                output_filename = f"{filename_base}_ansi{filename_ext}"
            else:
                output_filename = f"{filename_base}_utf8{filename_ext}"
                
            output_path = os.path.join(app.config['TEMP_FOLDER'], f"{filename_base}_{unique_id}_output{filename_ext}")
            
            # Read original content
            original_content, original_encoding = read_file(input_path)
            print(f"File read with encoding: {original_encoding}")
            
            # Convert file
            converter.convert_file(input_path, output_path, direction)
            
            # Read converted content
            converted_content, converted_encoding = read_file(output_path)
            print(f"Conversion complete. Output encoding: {converted_encoding}")
            
            # Print samples for debugging
            print(f"Input sample: '{original_content[:50]}...'")
            print(f"Output sample: '{converted_content[:50]}...'")
            
            # Create response
            response = {
                'original': original_content,
                'converted': converted_content,
                'original_encoding': original_encoding,
                'converted_encoding': converted_encoding,
                'filename': output_filename,
                'download_url': url_for('download_file', filename=os.path.basename(output_path))
            }
            
        else:
            # Text input
            input_text = request.form.get('text', '')
            
            if not input_text:
                print("Error: No text provided")
                return jsonify({'error': 'No text provided'}), 400
            
            print(f"Processing text input (length: {len(input_text)})")
            print(f"Input sample: '{input_text[:50]}...'")
            
            # Convert text
            if direction == 'utf8_to_ansi':
                converted_text = converter.utf8_to_ansi(input_text=input_text)
                output_encoding = 'ansi'
            else:
                converted_text = converter.ansi_to_utf8(input_text=input_text)
                output_encoding = 'utf-8'
            
            print(f"Output sample: '{converted_text[:50]}...'")
            
            # Generate unique filename for download
            unique_id = str(uuid.uuid4())
            if direction == 'utf8_to_ansi':
                output_filename = f"converted_{unique_id}_ansi.txt"
            else:
                output_filename = f"converted_{unique_id}_utf8.txt"
                
            output_path = os.path.join(app.config['TEMP_FOLDER'], output_filename)
            
            # Write to file for download
            with open(output_path, 'w', encoding=output_encoding) as f:
                f.write(converted_text)
            
            # Create response
            response = {
                'original': input_text,
                'converted': converted_text,
                'original_encoding': 'utf-8' if direction == 'utf8_to_ansi' else 'ansi',
                'converted_encoding': output_encoding,
                'filename': output_filename,
                'download_url': url_for('download_file', filename=output_filename)
            }
        
        print("Conversion response prepared successfully")
        return jsonify(response)
    
    except Exception as e:
        print(f"Error during conversion: {e}")
        traceback.print_exc()
        return jsonify({'error': str(e)}), 500

@app.route('/predict', methods=['POST'])
def direct_predict():
    """Direct API endpoint to test the predictor model"""
    try:
        data = request.get_json()
        if not data or 'text' not in data:
            return jsonify({'error': 'No text provided'}), 400
        
        input_text = data['text']
        print(f"Direct prediction request: '{input_text}'")
        
        # Check if we have a working predictor
        if not hasattr(predictor, 'model_loaded') or not predictor.model_loaded:
            print("Error: No working predictor available")
            return jsonify({'error': 'Predictor model not available'}), 500
        
        # Use predictor to restore diacritics
        result = predictor.predict(input_text)
        print(f"Prediction result: '{result}'")
        
        return jsonify({
            'input': input_text,
            'output': result
        })
    
    except Exception as e:
        print(f"Error during prediction: {e}")
        traceback.print_exc()
        return jsonify({'error': str(e)}), 500

@app.route('/download/<filename>')
def download_file(filename):
    """Download a converted file"""
    return send_from_directory(app.config['TEMP_FOLDER'], filename, as_attachment=True)

@app.errorhandler(413)
def request_entity_too_large(error):
    """Handle file too large error"""
    return jsonify({'error': 'File too large (max 5MB)'}), 413

def cleanup_temp_files():
    """Clean up temporary files older than 1 hour"""
    import time
    import glob
    
    # Get all files in temp directory
    files = glob.glob(os.path.join(app.config['TEMP_FOLDER'], '*'))
    
    # Current time
    current_time = time.time()
    
    # Delete files older than 1 hour (3600 seconds)
    for file in files:
        if os.path.isfile(file):
            file_age = current_time - os.path.getmtime(file)
            if file_age > 3600:
                try:
                    os.remove(file)
                    print(f"Deleted old temp file: {file}")
                except:
                    pass

if __name__ == '__main__':
    # Ensure temp directory exists
    os.makedirs(TEMP_DIR, exist_ok=True)
    
    # Clean up old temp files
    cleanup_temp_files()
    
    # Debug information
    print(f"Temp directory: {TEMP_DIR}")
    print(f"Model loaded: {hasattr(predictor, 'model_loaded') and predictor.model_loaded}")
    
    # Run Flask app
    app.run(debug=True, host='0.0.0.0', port=5000) 