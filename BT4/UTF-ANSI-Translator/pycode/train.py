# -*- coding: utf-8 -*-

import sys
import os

# Thêm thư mục hiện tại vào đường dẫn để import module
sys.path.append(os.path.dirname(os.path.abspath(__file__)))

from train.trainer import train_from_scratch

if __name__ == "__main__":
    train_from_scratch() 