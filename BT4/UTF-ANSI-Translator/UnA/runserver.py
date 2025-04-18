#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
RunServer script for UnA - UTF-8/ANSI Converter Web Application
"""

import os
import sys
import time
import logging
import webbrowser
import threading
import requests
from app import app, converter

# Configure logging
logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
    handlers=[
        logging.StreamHandler(sys.stdout)
    ]
)

logger = logging.getLogger("UnA")

def open_browser():
    """Open browser after a short delay to ensure server is running"""
    time.sleep(1)
    webbrowser.open('http://localhost:5000')

def check_model_service():
    """Check if the Model service is running"""
    try:
        response = requests.get("http://localhost:5001/status", timeout=2)
        if response.status_code == 200:
            logger.info("Model service is running correctly")
            return True
        else:
            logger.warning(f"Model service returned error: {response.status_code}")
            return False
    except Exception as e:
        logger.warning(f"Model service not available: {e}")
        return False

def main():
    """Main function to run the server"""
    # Current working directory
    cwd = os.getcwd()
    logger.info(f"Current working directory: {cwd}")
    
    # Check for Model service
    model_service_running = check_model_service()
    if not model_service_running:
        logger.warning("Model service is not running!")
        logger.warning("ANSI to UTF-8 conversion with diacritic restoration will not work")
        logger.warning("")
        logger.warning("To start the Model service, open a new terminal and run:")
        logger.warning("cd ../Model")
        logger.warning("python model_service.py")
        logger.warning("")
        
        # Ask user if they want to continue
        response = input("Do you want to continue without the Model service? (y/n): ")
        if response.lower() != 'y':
            logger.info("Exiting. Please start the Model service first.")
            sys.exit(0)
    
    # Print server information
    host = '0.0.0.0'
    port = 5000
    
    # Print welcome message
    print("="*60)
    print(" UnA - UTF-8/ANSI Converter & Vietnamese Diacritic Restorer")
    print("="*60)
    print(f" Server running at:")
    print(f" - Local:   http://localhost:{port}")
    
    # Get all IP addresses
    import socket
    try:
        hostname = socket.gethostname()
        ips = socket.gethostbyname_ex(hostname)[2]
        for ip in ips:
            if ip.startswith('192.168.') or ip.startswith('10.') or ip.startswith('172.'):
                print(f" - Network: http://{ip}:{port}")
    except:
        pass
    
    print("="*60)
    print(" Features:")
    print(" - UTF-8 to ANSI conversion")
    if model_service_running:
        print(" - ANSI to UTF-8 conversion with diacritic restoration (Model service running)")
    else:
        print(" - ANSI to UTF-8 conversion (Warning: Model service not running)")
    print("="*60)
    
    # Open browser automatically
    threading.Thread(target=open_browser).start()
    
    # Run the app
    app.run(debug=False, host=host, port=port)

if __name__ == '__main__':
    main() 