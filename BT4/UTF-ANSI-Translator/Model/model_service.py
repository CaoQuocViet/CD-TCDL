#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
Model Service for Vietnamese Diacritic Restoration
Runs as a standalone service using Flask
"""

import os
import sys
from flask import Flask, request, jsonify
from run_model import add_accent

# Create Flask app
app = Flask(__name__)

# Set port
PORT = 5001

@app.route('/predict', methods=['POST'])
def predict():
    """API endpoint to restore diacritics"""
    try:
        data = request.json
        if not data or 'text' not in data:
            return jsonify({"error": "Missing 'text' field in request"}), 400
        
        # Get input text
        input_text = data['text']
        
        # Process with model
        result = add_accent(input_text)
        
        # Return results
        return jsonify({
            "input": input_text,
            "output": result,
            "success": True
        })
    except Exception as e:
        return jsonify({"error": str(e), "success": False}), 500

@app.route('/status', methods=['GET'])
def status():
    """Check if the service is running"""
    return jsonify({"status": "Model service is running", "success": True})

if __name__ == '__main__':
    print("="*60)
    print(" Model Service for Vietnamese Diacritic Restoration")
    print("="*60)
    print(f" Service running at: http://localhost:{PORT}")
    print("="*60)
    
    # Run the app
    app.run(debug=False, host='0.0.0.0', port=PORT) 