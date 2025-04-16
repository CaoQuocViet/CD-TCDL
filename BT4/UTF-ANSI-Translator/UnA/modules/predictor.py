"""
Predictor module for UnA - handles integration with the trained model
"""
import os
import sys
import traceback
import re

class Predictor:
    def __init__(self):
        """
        Initialize the predictor with access to the pycode predict module
        """
        self.model_loaded = False
        self.predict_func = None
        
        # Get the project root directory
        parent_dir = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
        pycode_dir = os.path.join(parent_dir, 'pycode')
        
        print(f"Looking for pycode directory at: {pycode_dir}")
        
        if os.path.exists(pycode_dir):
            # Add pycode to path if needed
            if pycode_dir not in sys.path:
                sys.path.insert(0, pycode_dir)
            
            try:
                # Directly import predict_text function from predict.py
                print("Importing predict_text function from predict.py")
                from predict import predict_text
                self.predict_func = predict_text
                
                # Test the model with a simple sentence
                test_result = self.predict_func("day la thu nghiem")
                print(f"Test prediction result: '{test_result}'")
                
                self.model_loaded = True
                print("Predictor initialized successfully!")
            except Exception as e:
                print(f"Error importing predict_text function: {e}")
                traceback.print_exc()
                self.model_loaded = False
        else:
            print(f"Error: pycode directory not found at {pycode_dir}")
            self.model_loaded = False
    
    def predict(self, text):
        """
        Predict the diacritics for the given text
        
        Args:
            text: Input text without diacritics
            
        Returns:
            Text with diacritics restored
        """
        if not self.model_loaded or self.predict_func is None:
            print("Warning: Model not loaded, returning input text as is")
            return text
        
        try:
            # For longer texts, split into sentences and process separately
            if len(text) > 200:
                return self.predict_long_text(text)
            
            # Use the imported predict_text function
            print(f"Predicting diacritics for: '{text[:50]}...'")
            result = self.predict_func(text)
            print(f"Prediction result: '{result[:50]}...'")
            return result
        except Exception as e:
            print(f"Error during prediction: {e}")
            traceback.print_exc()
            return text
    
    def predict_long_text(self, text):
        """
        Process longer texts by splitting them into smaller chunks
        
        Args:
            text: Long input text without diacritics
            
        Returns:
            Text with diacritics restored
        """
        print(f"Processing long text with length: {len(text)}")
        
        # Split text into lines and process each line
        lines = text.split('\n')
        processed_lines = []
        
        for line in lines:
            # Skip empty lines
            if not line.strip():
                processed_lines.append(line)
                continue
                
            # Process sentences in each line
            sentences = re.split(r'([.!?])', line)
            processed_sentences = []
            
            current_chunk = ""
            for i in range(0, len(sentences), 2):
                sentence = sentences[i].strip()
                
                # Add punctuation mark if available
                if i + 1 < len(sentences):
                    sentence += sentences[i + 1]
                
                if not sentence:
                    continue
                    
                # Process each sentence
                try:
                    processed = self.predict_func(sentence)
                    processed_sentences.append(processed)
                except Exception as e:
                    print(f"Error processing sentence '{sentence}': {e}")
                    processed_sentences.append(sentence)
            
            processed_lines.append("".join(processed_sentences))
        
        return "\n".join(processed_lines) 