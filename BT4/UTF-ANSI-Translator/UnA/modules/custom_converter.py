"""
Custom converter module for UTF-8 to ANSI conversion
Implements manual conversion following the UTF-8 specification
"""

import unicodedata
from .utf8_utils import decode_utf8_bytes, encode_code_points_to_utf8

class CustomConverter:
    """Custom UTF-8 to ANSI converter class with manual implementation"""
    
    def __init__(self):
        # Map of common Vietnamese characters to their ASCII equivalents
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
    
    def utf8_to_ascii_manual(self, input_bytes):
        """
        Manual conversion from UTF-8 to ASCII by directly working with bytes
        
        Args:
            input_bytes: UTF-8 encoded bytes
            
        Returns:
            ASCII bytes
        """
        # Decode UTF-8 bytes to Unicode code points
        code_points = decode_utf8_bytes(input_bytes)
        
        # Convert each code point to ASCII if possible
        ascii_code_points = []
        for cp in code_points:
            # If it's an ASCII character (0-127), keep it as is
            if cp <= 0x7F:
                ascii_code_points.append(cp)
            else:
                # Try to convert non-ASCII Unicode to ASCII
                try:
                    # Convert code point to character
                    char = chr(cp)
                    
                    # Check if it's in our Vietnamese map
                    if char in self.vietnamese_map:
                        # Convert to ASCII equivalent
                        ascii_char = self.vietnamese_map[char]
                        ascii_code_points.append(ord(ascii_char))
                    else:
                        # Try to decompose the character and keep only the base letter
                        normalized = unicodedata.normalize('NFD', char)
                        base_char = normalized[0]  # Take just the base character
                        
                        # If base character is ASCII, use it
                        if ord(base_char) <= 0x7F:
                            ascii_code_points.append(ord(base_char))
                        else:
                            # If we can't convert, replace with '?'
                            ascii_code_points.append(ord('?'))
                except:
                    # If there's any error, replace with '?'
                    ascii_code_points.append(ord('?'))
        
        # Convert code points to bytes
        return bytes(ascii_code_points)
    
    def ascii_to_utf8_manual(self, input_bytes, predictor=None):
        """
        Manual conversion from ASCII to UTF-8
        This is a placeholder as the actual conversion to add diacritics 
        requires a predictor model
        
        Args:
            input_bytes: ASCII encoded bytes
            predictor: Optional predictor model for restoring diacritics
            
        Returns:
            UTF-8 encoded bytes
        """
        # If we have a predictor, use it
        if predictor:
            # Convert ASCII bytes to string
            ascii_text = input_bytes.decode('ascii', errors='replace')
            
            # Use predictor to restore diacritics
            utf8_text = predictor.predict(ascii_text)
            
            # Convert back to UTF-8 bytes
            return utf8_text.encode('utf-8')
        
        # If no predictor, just return the input as UTF-8
        # This won't add any diacritics
        return input_bytes
    
    def utf8_to_ascii(self, input_text=None, input_file=None, output_file=None):
        """
        Convert UTF-8 text with diacritics to ASCII without diacritics
        
        Args:
            input_text: Text to convert
            input_file: Path to input file
            output_file: Path to output file
            
        Returns:
            Converted text and/or path to output file
        """
        # Get input bytes
        if input_file:
            with open(input_file, 'rb') as f:
                input_bytes = f.read()
        else:
            input_bytes = input_text.encode('utf-8')
        
        # Convert to ASCII
        ascii_bytes = self.utf8_to_ascii_manual(input_bytes)
        
        # Convert bytes to string
        result = ascii_bytes.decode('ascii', errors='replace')
        
        # Write to output file if specified
        if output_file:
            with open(output_file, 'wb') as f:
                f.write(ascii_bytes)
            return result, output_file
        
        return result 