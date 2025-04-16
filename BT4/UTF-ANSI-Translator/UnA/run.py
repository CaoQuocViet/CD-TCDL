#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
Run script for UnA - UTF-8/ANSI Converter
This script will simply import and run the main app.py
"""

import os
import sys
import traceback

def main():
    # Add the current directory to the path
    current_dir = os.path.dirname(os.path.abspath(__file__))
    if current_dir not in sys.path:
        sys.path.append(current_dir)
    
    # Add parent directory to path to potentially find pycode
    parent_dir = os.path.dirname(current_dir)
    if parent_dir not in sys.path:
        sys.path.append(parent_dir)
    
    # Check for model files
    result_dir = os.path.join(parent_dir, 'result')
    if os.path.exists(result_dir):
        print(f"Found result directory at: {result_dir}")
        model_path = os.path.join(result_dir, 'restore_diacritic.keras')
        source_vec_path = os.path.join(result_dir, 'source_vectorization_layer.pkl')
        target_vec_path = os.path.join(result_dir, 'target_vectorization_layer.pkl')
        
        print(f"Model file exists: {os.path.exists(model_path)}")
        print(f"Source vectorization exists: {os.path.exists(source_vec_path)}")
        print(f"Target vectorization exists: {os.path.exists(target_vec_path)}")
    else:
        print(f"Warning: Result directory not found at {result_dir}")
    
    # Check for pycode directory
    pycode_dir = os.path.join(parent_dir, 'pycode')
    if os.path.exists(pycode_dir):
        print(f"Found pycode directory at: {pycode_dir}")
        models_dir = os.path.join(pycode_dir, 'models')
        if os.path.exists(models_dir):
            print(f"Found models directory at: {models_dir}")
            # Add to sys.path
            if models_dir not in sys.path:
                sys.path.append(models_dir)
    else:
        print(f"Warning: Pycode directory not found at {pycode_dir}")
    
    # Import and run the app
    try:
        print("Initializing UnA application...")
        
        # Import the modules
        from modules.predictor import Predictor
        
        # Test predictor with example
        print("Testing predictor with sample text...")
        predictor = Predictor()
        if hasattr(predictor, 'model_loaded') and predictor.model_loaded:
            test_text = "day la mot thu nghiem"
            result = predictor.predict(test_text)
            print(f"Sample prediction: '{test_text}' -> '{result}'")
        else:
            print("Warning: Predictor not loaded correctly")
        
        # Import and run the app
        from app import app
        
        print("\nStarting UnA - UTF-8/ANSI Converter...")
        print("Open your browser and go to http://localhost:5000")
        print("Press Ctrl+C to stop the server")
        
        app.run(debug=True, host='0.0.0.0', port=5000)
    except ImportError as e:
        print(f"Error importing app: {e}")
        traceback.print_exc()
        print("Make sure you are in the correct directory and have installed all requirements")
        sys.exit(1)
    except Exception as e:
        print(f"Error running app: {e}")
        traceback.print_exc()
        sys.exit(1)

if __name__ == "__main__":
    main() 