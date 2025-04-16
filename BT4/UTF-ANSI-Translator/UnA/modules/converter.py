"""
Converter module for UnA - handles UTF-8 to ANSI and ANSI to UTF-8 conversions
"""
import os
import unidecode
import traceback
from .utils import read_file, write_file, get_temp_directory
from .custom_converter import CustomConverter

class Converter:
    def __init__(self, predictor=None):
        """
        Initialize the converter
        
        Args:
            predictor: Optional predictor model for ANSI to UTF-8 conversion
        """
        self.predictor = predictor
        self.temp_dir = get_temp_directory()
        self.custom_converter = CustomConverter()
        
        # Check if predictor is loaded correctly
        if predictor is not None:
            if hasattr(predictor, 'model_loaded') and predictor.model_loaded:
                print("Converter initialized with working predictor model")
                # Test predictor
                test_text = "test khoi phuc dau"
                result = predictor.predict(test_text)
                print(f"Test result: '{test_text}' -> '{result}'")
            else:
                print("Warning: Predictor is provided but model is not loaded correctly")
        else:
            print("Warning: No predictor provided, diacritic restoration will not work")
    
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
        
        # Use custom converter for manual conversion
        if input_file:
            print(f"Converting file: {input_file}")
            result = self.custom_converter.utf8_to_ascii(input_file=input_file, output_file=output_file)
            if output_file:
                print(f"Result saved to: {output_file}")
                return result  # Returns (text, output_file) already
            return result
        else:
            # Use custom converter for text input
            print(f"Converting text input (length: {len(input_text) if input_text else 0})")
            result = self.custom_converter.utf8_to_ascii(input_text=input_text)
            
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
        
        # Check if we have a working predictor
        if self.predictor is None or not hasattr(self.predictor, 'model_loaded') or not self.predictor.model_loaded:
            print("Warning: No working predictor model available, diacritics will not be restored")
            result = input_text
        else:
            try:
                # Use predictor model to restore diacritics
                print(f"Using predictor to restore diacritics")
                result = self.predictor.predict(input_text)
                print(f"Diacritics restored. Sample: '{input_text[:50]}' -> '{result[:50]}'")
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