#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import os

# Thêm thư mục hiện tại vào đường dẫn để import module
sys.path.append(os.path.dirname(os.path.abspath(__file__)))

from models.transformer_model import TransformerModel

def predict_text(input_text):
    """
    Dự đoán văn bản dùng mô hình đã được huấn luyện
    """
    transformer = TransformerModel(
        source_vectorization='../result/source_vectorization_layer.pkl',
        target_vectorization='../result/target_vectorization_layer.pkl',
        model_path='../result/restore_diacritic.keras'
    )
    
    return transformer.predict(input_text)

def predict_file(input_file, output_file):
    """
    Dự đoán từ file văn bản và lưu kết quả
    """
    transformer = TransformerModel(
        source_vectorization='../result/source_vectorization_layer.pkl',
        target_vectorization='../result/target_vectorization_layer.pkl',
        model_path='../result/restore_diacritic.keras'
    )
    
    with open(input_file, 'r', encoding='utf-8') as f:
        lines = f.readlines()
    
    results = []
    for line in lines:
        line = line.strip()
        if line:
            predicted = transformer.predict(line)
            results.append(predicted + '\n')
    
    with open(output_file, 'w', encoding='utf-8') as f:
        f.writelines(results)
    
    print(f"Đã dự đoán và lưu kết quả vào {output_file}")

if __name__ == "__main__":
    if len(sys.argv) == 1:
        # Interactive mode
        print("Nhập văn bản cần dự đoán (gõ 'exit' để thoát):")
        while True:
            input_text = input("> ")
            if input_text.lower() == 'exit':
                break
            print(predict_text(input_text))
    elif len(sys.argv) == 3:
        # File mode
        input_file = sys.argv[1]
        output_file = sys.argv[2]
        predict_file(input_file, output_file)
    else:
        print("Sử dụng:")
        print("  python predict.py                     # Chế độ tương tác")
        print("  python predict.py input.txt output.txt  # Dự đoán từ file") 