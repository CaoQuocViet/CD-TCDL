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
        
        # Vietnamese character mapping for direct conversion
        self.vietnamese_map = {
            # lowercase
            'á': 'a', 'à': 'a', 'ả': 'a', 'ã': 'a', 'ạ': 'a',
            'ă': 'a', 'ắ': 'a', 'ằ': 'a', 'ẳ': 'a', 'ẵ': 'a', 'ặ': 'a',
            'â': 'a', 'ấ': 'a', 'ầ': 'a', 'ẩ': 'a', 'ẫ': 'a', 'ậ': 'a',
            'đ': 'd',
            'é': 'e', 'è': 'e', 'ẻ': 'e', 'ẽ': 'e', 'ẹ': 'e',
            'ê': 'e', 'ế': 'e', 'ề': 'e', 'ể': 'e', 'ễ': 'e', 'ệ': 'e',
            'í': 'i', 'ì': 'i', 'ỉ': 'i', 'ĩ': 'i', 'ị': 'i',
            'ó': 'o', 'ò': 'o', 'ỏ': 'o', 'õ': 'o', 'ọ': 'o',
            'ô': 'o', 'ố': 'o', 'ồ': 'o', 'ổ': 'o', 'ỗ': 'o', 'ộ': 'o',
            'ơ': 'o', 'ớ': 'o', 'ờ': 'o', 'ở': 'o', 'ỡ': 'o', 'ợ': 'o',
            'ú': 'u', 'ù': 'u', 'ủ': 'u', 'ũ': 'u', 'ụ': 'u',
            'ư': 'u', 'ứ': 'u', 'ừ': 'u', 'ử': 'u', 'ữ': 'u', 'ự': 'u',
            'ý': 'y', 'ỳ': 'y', 'ỷ': 'y', 'ỹ': 'y', 'ỵ': 'y',
            
            # uppercase
            'Á': 'A', 'À': 'A', 'Ả': 'A', 'Ã': 'A', 'Ạ': 'A',
            'Ă': 'A', 'Ắ': 'A', 'Ằ': 'A', 'Ẳ': 'A', 'Ẵ': 'A', 'Ặ': 'A',
            'Â': 'A', 'Ấ': 'A', 'Ầ': 'A', 'Ẩ': 'A', 'Ẫ': 'A', 'Ậ': 'A',
            'Đ': 'D',
            'É': 'E', 'È': 'E', 'Ẻ': 'E', 'Ẽ': 'E', 'Ẹ': 'E',
            'Ê': 'E', 'Ế': 'E', 'Ề': 'E', 'Ể': 'E', 'Ễ': 'E', 'Ệ': 'E',
            'Í': 'I', 'Ì': 'I', 'Ỉ': 'I', 'Ĩ': 'I', 'Ị': 'I',
            'Ó': 'O', 'Ò': 'O', 'Ỏ': 'O', 'Õ': 'O', 'Ọ': 'O',
            'Ô': 'O', 'Ố': 'O', 'Ồ': 'O', 'Ổ': 'O', 'Ỗ': 'O', 'Ộ': 'O',
            'Ơ': 'O', 'Ớ': 'O', 'Ờ': 'O', 'Ở': 'O', 'Ỡ': 'O', 'Ợ': 'O',
            'Ú': 'U', 'Ù': 'U', 'Ủ': 'U', 'Ũ': 'U', 'Ụ': 'U',
            'Ư': 'U', 'Ứ': 'U', 'Ừ': 'U', 'Ử': 'U', 'Ữ': 'U', 'Ự': 'U',
            'Ý': 'Y', 'Ỳ': 'Y', 'Ỷ': 'Y', 'Ỹ': 'Y', 'Ỵ': 'Y'
        }
        
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
        
        # Convert each character individually using our mapping
        result = ""
        for char in input_text:
            if char in self.vietnamese_map:
                result += self.vietnamese_map[char]
            elif ord(char) < 128:  # ASCII character
                result += char
            else:
                # Replace any non-ASCII character with ?
                result += '?'
        
        # Write to output file if specified
        if output_file:
            print(f"Saving result to: {output_file}")
            # Use encoding='ascii' with errors='replace' to handle non-ASCII characters safely
            try:
                write_file(output_file, result, encoding='ascii', errors='replace')
            except Exception as e:
                print(f"Error writing file: {e}")
                traceback.print_exc()
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
                # Split text into lines to preserve line breaks
                lines = input_text.splitlines()
                processed_lines = []
                
                # Process each line separately
                for line in lines:
                    if line.strip():  # Skip empty lines but keep them
                        # Use model service to restore diacritics
                        print(f"Processing line: {line[:30]}...")
                        response = requests.post(
                            f"{self.model_service_url}/predict",
                            json={"text": line},
                            timeout=30
                        )
                        
                        if response.status_code == 200:
                            data = response.json()
                            processed_lines.append(data["output"])
                        else:
                            print(f"Error from model service: {response.text}")
                            processed_lines.append(line)
                    else:
                        processed_lines.append(line)  # Keep empty lines
                
                # Join the lines back together
                result = '\n'.join(processed_lines)
                print(f"Diacritics restored with {len(lines)} lines preserved")
                
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