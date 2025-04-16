# -*- coding: utf-8 -*-

import tensorflow as tf
import sys
import os

# Thêm thư mục cha vào đường dẫn để import module
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from data.data_loader import (create_vectorizations, load_data, make_dataset,
                         save_vectorization, load_vectorization_from_disk)
from models.transformer_model import TransformerModel

# Giảm batch size để tránh lỗi out of memory
batch_size = 32

# Sửa đường dẫn file
file_path = '../result/output.txt'
# Giới hạn số từ là 15000 (tương đương khoảng 5000 từ)
train_pairs, val_pairs, test_pairs = load_data(file_path, limit=15000)

callbacks=[
    tf.keras.callbacks.ModelCheckpoint(
        filepath='../result/restore_diacritic.keras',
        save_best_only='True',
        monitor='val_accuracy'
    )
]

def train_from_scratch():
    # Tăng sequence_length lên 150 để xử lý các câu dài hơn
    sequence_length = 150
    source_vectorization, target_vectorization = create_vectorizations(train_pairs, sequence_length=sequence_length)
    save_vectorization(source_vectorization, '../result/source_vectorization_layer.pkl')
    save_vectorization(target_vectorization, '../result/target_vectorization_layer.pkl')

    train_ds = make_dataset(train_pairs, source_vectorization, target_vectorization, batch_size)
    val_ds = make_dataset(val_pairs, source_vectorization, target_vectorization, batch_size)

    # Điều chỉnh mô hình với sequence_length tương ứng
    transformer = TransformerModel(source_vectorization=source_vectorization,
        target_vectorization=target_vectorization,
        sequence_length=sequence_length,
        dense_dim=2048,  # Giảm kích thước để tránh lỗi OOM
        num_heads=4,     # Giảm số lượng head
        drop_out=0)
    transformer.build_model(optimizer="rmsprop",
        loss="sparse_categorical_crossentropy",
        metrics=["accuracy"])
    transformer.fit(train_ds, epochs=30, validation_data=val_ds, callbacks=callbacks)

    test_ds = make_dataset(test_pairs, source_vectorization, target_vectorization, batch_size)
    transformer.evaluate(test_ds)

    print(transformer.predict('mot ngay troi nang mot ngay troi mua'))
    print(transformer.predict('toi sinh ra o ha noi'))
    print(transformer.predict('em con nho hay em da quen'))
    print(transformer.predict('ten toi la thai duong'))

def continue_training():
    source_vectorization = load_vectorization_from_disk('../result/source_vectorization_layer_cont.pkl')
    target_vectorization = load_vectorization_from_disk('../result/target_vectorization_layer_cont.pkl')

    train_ds = make_dataset(train_pairs, source_vectorization, target_vectorization, batch_size)
    val_ds = make_dataset(val_pairs, source_vectorization, target_vectorization, batch_size)

    transformer = TransformerModel(source_vectorization=source_vectorization,
        target_vectorization=target_vectorization,
        model_path='../result/restore_diacritic_cont.keras')
    transformer.fit(train_ds, epochs=5, validation_data=val_ds, callbacks=callbacks)

    test_ds = make_dataset(test_pairs, source_vectorization, target_vectorization, batch_size)
    transformer.evaluate(test_ds)

    print(transformer.predict('mot ngay troi nang mot ngay troi mua'))
    print(transformer.predict('toi sinh ra o ha noi'))
    print(transformer.predict('em con nho hay em da quen'))
    print(transformer.predict('ten toi la thai duong'))

if __name__ == "__main__":
    train_from_scratch()
