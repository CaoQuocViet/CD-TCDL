"""
Converter module for UnA - handles UTF-8 to ANSI and ANSI to UTF-8 conversions
"""
import os
import unidecode
import requests
import traceback
from .utils import read_file, write_file, get_temp_directory

class Converter:
    def __init__(self):
        """Initialize the converter"""
        self.temp_dir = get_temp_directory()
        self.model_service_url = "http://localhost:5001"
        
        # Check if model service is running
        try:
            response = requests.get(f"{self.model_service_url}/status", timeout=2)
            if response.status_code == 200:
                print("Model service is running and available")
                self.model_service_available = True
            else:
                print("Model service returned an error response")
                self.model_service_available = False
        except Exception as e:
            print(f"Warning: Could not connect to model service: {e}")
            self.model_service_available = False
    
    def utf8_to_ansi(self, input_text=None, input_file=None, output_file=None):
        """
        Convert UTF-8 text with diacritics to ANSI without diacritics
        
        Args:
            input_text: Text to convert
            input_file: Path to input file
            output_file: Path to output file
            
        Returns:
            Converted text and/or path to output file
        """
        print(f"UTF-8 to ANSI conversion started")
        
        # Get input text
        if input_file:
            print(f"Reading file: {input_file}")
            input_text, encoding = read_file(input_file)
            print(f"File read with encoding: {encoding}")
        
        # Use unidecode for simple conversion
        result = unidecode.unidecode(input_text)
        
        # Write to output file if specified
        if output_file:
            print(f"Saving result to: {output_file}")
            write_file(output_file, result, encoding='ansi')
            return result, output_file
        
        print(f"Conversion completed")
        return result
    
    def ansi_to_utf8(self, input_text=None, input_file=None, output_file=None):
        """
        Convert ANSI text without diacritics to UTF-8 with diacritics
        
        Args:
            input_text: Text to convert
            input_file: Path to input file
            output_file: Path to output file
            
        Returns:
            Converted text and/or path to output file
        """
        print(f"ANSI to UTF-8 conversion started")
        
        # Get input text
        if input_file:
            print(f"Reading file: {input_file}")
            input_text, encoding = read_file(input_file, encoding='ansi')
            print(f"File read with encoding: {encoding}")
        
        # Check if model service is available
        if not self.model_service_available:
            print("Warning: Model service not available, diacritics will not be restored")
            result = input_text
        else:
            try:
                # Use model service to restore diacritics
                print(f"Using model service to restore diacritics")
                response = requests.post(
                    f"{self.model_service_url}/predict",
                    json={"text": input_text},
                    timeout=30
                )
                
                if response.status_code == 200:
                    data = response.json()
                    result = data["output"]
                    print(f"Diacritics restored. Sample: '{input_text[:50]}' -> '{result[:50]}'")
                else:
                    print(f"Error from model service: {response.text}")
                    result = input_text
            except Exception as e:
                print(f"Error during diacritic restoration: {e}")
                traceback.print_exc()
                result = input_text
        
        # Write to output file if specified
        if output_file:
            print(f"Saving result to: {output_file}")
            write_file(output_file, result, encoding='utf-8')
            return result, output_file
        
        print(f"Conversion completed")
        return result
    
    def convert_file(self, input_file, output_file, direction):
        """
        Convert a file based on the specified direction
        
        Args:
            input_file: Path to input file
            output_file: Path to output file
            direction: 'utf8_to_ansi' or 'ansi_to_utf8'
            
        Returns:
            Path to output file
        """
        print(f"Converting file: {input_file} -> {output_file} (Direction: {direction})")
        
        try:
            if direction == 'utf8_to_ansi':
                _, output_path = self.utf8_to_ansi(input_file=input_file, output_file=output_file)
            elif direction == 'ansi_to_utf8':
                _, output_path = self.ansi_to_utf8(input_file=input_file, output_file=output_file)
            else:
                raise ValueError(f"Unknown direction: {direction}")
            
            print(f"Conversion successful: {output_path}")
            return output_path
        except Exception as e:
            print(f"Error during file conversion: {e}")
            traceback.print_exc()
            raise 