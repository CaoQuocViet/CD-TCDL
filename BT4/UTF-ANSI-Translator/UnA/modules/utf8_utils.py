"""
UTF-8 utility functions for manual encoding/decoding
Based on UTF-8 specification:

Code point ↔ UTF-8 conversion
First code point	Last code point	Byte 1	Byte 2	Byte 3	Byte 4
U+0000	        U+007F	        0yyyzzzz	
U+0080	        U+07FF	        110xxxyy	10yyzzzz	
U+0800	        U+FFFF	        1110wwww	10xxxxyy	10yyzzzz	
U+010000	    U+10FFFF	    11110uvv	10vvwwww	10xxxxyy	10yyzzzz

"""

def utf8_to_code_point(bytes_sequence):
    """
    Convert a UTF-8 byte sequence to a Unicode code point
    
    Args:
        bytes_sequence: A bytes object containing a UTF-8 encoded character
        
    Returns:
        The Unicode code point as an integer
    """
    # Handle single byte (ASCII) - 0xxxxxxx
    if len(bytes_sequence) == 1:
        return bytes_sequence[0]
    
    # Handle two bytes - 110xxxxx 10xxxxxx
    elif len(bytes_sequence) == 2:
        # Extract bits from first byte (110xxxxx) - take 5 bits
        bits_from_first = bytes_sequence[0] & 0b00011111
        
        # Extract bits from second byte (10xxxxxx) - take 6 bits
        bits_from_second = bytes_sequence[1] & 0b00111111
        
        # Combine the bits
        return (bits_from_first << 6) | bits_from_second
    
    # Handle three bytes - 1110xxxx 10xxxxxx 10xxxxxx
    elif len(bytes_sequence) == 3:
        # Extract bits from first byte (1110xxxx) - take 4 bits
        bits_from_first = bytes_sequence[0] & 0b00001111
        
        # Extract bits from second byte (10xxxxxx) - take 6 bits
        bits_from_second = bytes_sequence[1] & 0b00111111
        
        # Extract bits from third byte (10xxxxxx) - take 6 bits
        bits_from_third = bytes_sequence[2] & 0b00111111
        
        # Combine the bits
        return (bits_from_first << 12) | (bits_from_second << 6) | bits_from_third
    
    # Handle four bytes - 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
    elif len(bytes_sequence) == 4:
        # Extract bits from first byte (11110xxx) - take 3 bits
        bits_from_first = bytes_sequence[0] & 0b00000111
        
        # Extract bits from second byte (10xxxxxx) - take 6 bits
        bits_from_second = bytes_sequence[1] & 0b00111111
        
        # Extract bits from third byte (10xxxxxx) - take 6 bits
        bits_from_third = bytes_sequence[2] & 0b00111111
        
        # Extract bits from fourth byte (10xxxxxx) - take 6 bits
        bits_from_fourth = bytes_sequence[3] & 0b00111111
        
        # Combine the bits
        return (bits_from_first << 18) | (bits_from_second << 12) | (bits_from_third << 6) | bits_from_fourth
    
    else:
        raise ValueError(f"Invalid UTF-8 byte sequence length: {len(bytes_sequence)}")

def code_point_to_utf8(code_point):
    """
    Convert a Unicode code point to a UTF-8 byte sequence
    
    Args:
        code_point: The Unicode code point as an integer
        
    Returns:
        A bytes object containing the UTF-8 encoded character
    """
    # U+0000 to U+007F: 0xxxxxxx
    if code_point <= 0x7F:
        return bytes([code_point])
    
    # U+0080 to U+07FF: 110xxxxx 10xxxxxx
    elif code_point <= 0x7FF:
        byte1 = 0b11000000 | (code_point >> 6)
        byte2 = 0b10000000 | (code_point & 0b00111111)
        return bytes([byte1, byte2])
    
    # U+0800 to U+FFFF: 1110xxxx 10xxxxxx 10xxxxxx
    elif code_point <= 0xFFFF:
        byte1 = 0b11100000 | (code_point >> 12)
        byte2 = 0b10000000 | ((code_point >> 6) & 0b00111111)
        byte3 = 0b10000000 | (code_point & 0b00111111)
        return bytes([byte1, byte2, byte3])
    
    # U+10000 to U+10FFFF: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
    elif code_point <= 0x10FFFF:
        byte1 = 0b11110000 | (code_point >> 18)
        byte2 = 0b10000000 | ((code_point >> 12) & 0b00111111)
        byte3 = 0b10000000 | ((code_point >> 6) & 0b00111111)
        byte4 = 0b10000000 | (code_point & 0b00111111)
        return bytes([byte1, byte2, byte3, byte4])
    
    else:
        raise ValueError(f"Code point {code_point} is outside the valid Unicode range")

def decode_utf8_bytes(data):
    """
    Decode a bytes object containing UTF-8 encoded data into a list of code points
    
    Args:
        data: A bytes object containing UTF-8 encoded data
        
    Returns:
        A list of Unicode code points
    """
    code_points = []
    i = 0
    
    while i < len(data):
        # Determine the number of bytes in the current character
        if (data[i] & 0b10000000) == 0:  # 0xxxxxxx
            num_bytes = 1
        elif (data[i] & 0b11100000) == 0b11000000:  # 110xxxxx
            num_bytes = 2
        elif (data[i] & 0b11110000) == 0b11100000:  # 1110xxxx
            num_bytes = 3
        elif (data[i] & 0b11111000) == 0b11110000:  # 11110xxx
            num_bytes = 4
        else:
            # Invalid UTF-8 byte sequence
            i += 1
            continue
        
        # Check if we have enough bytes
        if i + num_bytes > len(data):
            break
        
        # Extract the code point
        try:
            code_point = utf8_to_code_point(data[i:i+num_bytes])
            code_points.append(code_point)
        except:
            # Skip if there's an error
            pass
        
        i += num_bytes
    
    return code_points

def encode_code_points_to_utf8(code_points):
    """
    Encode a list of code points into a UTF-8 encoded bytes object
    
    Args:
        code_points: A list of Unicode code points
        
    Returns:
        A bytes object containing the UTF-8 encoded data
    """
    result = b""
    
    for code_point in code_points:
        try:
            result += code_point_to_utf8(code_point)
        except:
            # Skip if there's an error
            pass
    
    return result

def is_valid_utf8(data):
    """
    Check if a bytes object contains valid UTF-8 encoded data
    
    Args:
        data: A bytes object
        
    Returns:
        True if the data is valid UTF-8, False otherwise
    """
    try:
        data.decode('utf-8')
        return True
    except UnicodeDecodeError:
        return False 