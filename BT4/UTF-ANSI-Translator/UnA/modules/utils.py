"""
Utility functions for the UnA converter
"""
import os
import chardet
import unidecode
import re

def detect_encoding(file_path):
    """
    Detect the encoding of a file
    """
    with open(file_path, 'rb') as file:
        raw_data = file.read()
        result = chardet.detect(raw_data)
        if result and result['encoding']:
            return result['encoding']
        # Default to utf-8 if detection fails
        return 'utf-8'

def read_file(file_path, encoding=None):
    """
    Read a file with the specified encoding or detect it automatically
    """
    if not encoding:
        encoding = detect_encoding(file_path)
    
    # Ensure we have a valid encoding
    if not encoding:
        encoding = 'utf-8'  # Use UTF-8 as fallback
    
    try:
        with open(file_path, 'r', encoding=encoding) as file:
            return file.read(), encoding
    except UnicodeDecodeError:
        # Fallback to binary mode and try to decode
        with open(file_path, 'rb') as file:
            raw_data = file.read()
            # Try several common encodings
            for enc in ['utf-8', 'cp1252', 'latin-1', 'ascii']:
                try:
                    return raw_data.decode(enc, errors='replace'), enc
                except UnicodeDecodeError:
                    continue
            
            # If all fail, use latin-1 which can decode any byte sequence
            return raw_data.decode('latin-1', errors='replace'), 'latin-1'

def write_file(file_path, content, encoding, errors='strict'):
    """
    Write content to a file with the specified encoding
    
    Args:
        file_path: Path to the output file
        content: Content to write
        encoding: Encoding to use
        errors: How to handle encoding errors ('strict', 'replace', 'ignore')
    """
    # Ensure we have a valid encoding
    if not encoding:
        encoding = 'utf-8'  # Use UTF-8 as fallback
        
    with open(file_path, 'w', encoding=encoding, errors=errors) as file:
        file.write(content)
    return file_path

def is_vietnamese_text(text):
    """
    Simple check to determine if the text is likely Vietnamese
    """
    # Check for common Vietnamese diacritical marks or characters
    vietnamese_pattern = re.compile(r'[àáạảãâầấậẩẫăằắặẳẵèéẹẻẽêềếệểễìíịỉĩòóọỏõôồốộổỗơờớợởỡùúụủũưừứựửữỳýỵỷỹđ]', 
                                    re.IGNORECASE)
    return bool(vietnamese_pattern.search(text))

def get_temp_directory():
    """
    Get or create a temporary directory for file operations
    """
    temp_dir = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), 'temp')
    os.makedirs(temp_dir, exist_ok=True)
    return temp_dir 