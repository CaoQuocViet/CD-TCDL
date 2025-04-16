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

    print(transformer.predict('1. Ha Noi la thu do cua Viet Nam, noi tieng voi lich su lau doi va van hoa dac sac.'))
    print(transformer.predict('2. Ha Long Bay la mot trong nhung di san thien nhien the gioi duoc UNESCO cong nhan.'))
    print(transformer.predict('3. Viet Nam co nen am thuc phong phu voi nhieu mon an ngon, dac biet la pho.'))
    print(transformer.predict('4. Sai Gon luon la thanh pho nhon nhip va day nang dong.'))
    print(transformer.predict('5. Nguoi dan Viet Nam rat hieu khach va than thien.'))
    print(transformer.predict('6. Tet Nguyen Dan la le hoi lon nhat trong nam o Viet Nam.'))
    print(transformer.predict('7. Duong pho Ha Noi dep nhat vao mua thu khi la vang roi.'))
    print(transformer.predict('8. Cac mon an vat duong pho o Viet Nam rat hap dan va phong phu.'))
    print(transformer.predict('9. Dia danh Hoi An noi tieng voi nhung ngoi nha co kin va anh den long lung linh.'))
    print(transformer.predict('10. Viet Nam co nhieu canh dep thien nhien hung vi, tu nui rung den bien ca.'))

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

    print(transformer.predict('1. Ha Noi la thu do cua Viet Nam, noi tieng voi lich su lau doi va van hoa dac sac.'))
    print(transformer.predict('2. Ha Long Bay la mot trong nhung di san thien nhien the gioi duoc UNESCO cong nhan.'))
    print(transformer.predict('3. Viet Nam co nen am thuc phong phu voi nhieu mon an ngon, dac biet la pho.'))
    print(transformer.predict('4. Sai Gon luon la thanh pho nhon nhip va day nang dong.'))
    print(transformer.predict('5. Nguoi dan Viet Nam rat hieu khach va than thien.'))
    print(transformer.predict('6. Tet Nguyen Dan la le hoi lon nhat trong nam o Viet Nam.'))
    print(transformer.predict('7. Duong pho Ha Noi dep nhat vao mua thu khi la vang roi.'))
    print(transformer.predict('8. Cac mon an vat duong pho o Viet Nam rat hap dan va phong phu.'))
    print(transformer.predict('9. Dia danh Hoi An noi tieng voi nhung ngoi nha co kin va anh den long lung linh.'))
    print(transformer.predict('10. Viet Nam co nhieu canh dep thien nhien hung vi, tu nui rung den bien ca.'))

if __name__ == "__main__":
    train_from_scratch()
