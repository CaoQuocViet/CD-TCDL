# Vietnamese Diacritic Restoration

Transformer-based model to restore Vietnamese diacritics.

## ⚙️ Cấu hình & Chạy dự án

### Chuẩn bị dữ liệu

1. Tải và giải nén dataset từ Kaggle:  
   [Old Newspaper Dataset](https://www.kaggle.com/alvations/old-newspapers)

2. Chạy lệnh sau để xử lý dữ liệu đầu vào:
```bash
dotnet run <input file path> <output file path>
```

---

### Huấn luyện mô hình

```python
from data_loader import load_data, make_dataset, save_vectorization
from transformer_model import TransformerModel

# Load và xử lý dữ liệu
train_pairs, val_pairs, test_pairs = load_data('dataset/old-newspaper-vietnamese.txt', limit=10000)

# Vectorization
source_vectorization, target_vectorization = create_vectorizations(train_pairs)
save_vectorization(source_vectorization, 'result/source_vectorization_layer.pkl')
save_vectorization(target_vectorization, 'result/target_vectorization_layer.pkl')

# Dataset
train_ds = make_dataset(train_pairs, source_vectorization, target_vectorization, batch_size=64)
val_ds = make_dataset(val_pairs, source_vectorization, target_vectorization, batch_size=64)

# Mô hình
transformer = TransformerModel(
    source_vectorization=source_vectorization,
    target_vectorization=target_vectorization,
    dense_dim=8192,
    num_heads=8,
    drop_out=0
)

transformer.build_model(
    optimizer="rmsprop",
    loss="sparse_categorical_crossentropy",
    metrics=["accuracy"]
)

transformer.fit(
    train_ds,
    epochs=50,
    validation_data=val_ds
)
```

---

### Dự đoán bằng mô hình đã huấn luyện

```python
transformer = TransformerModel(
    source_vectorization='result/source_vectorization_layer_cont.pkl',
    target_vectorization='result/target_vectorization_layer_cont.pkl',
    model_path='result/restore_diacritic.keras'
)

print(transformer.predict('co phai em la mua thu ha noi'))
```

---

### Tiếp tục huấn luyện từ checkpoint

```python
from data_loader import load_vectorization_from_disk

source_vectorization = load_vectorization_from_disk('result/source_vectorization_layer_cont.pkl')
target_vectorization = load_vectorization_from_disk('result/target_vectorization_layer_cont.pkl')

transformer = TransformerModel(
    source_vectorization=source_vectorization,
    target_vectorization=target_vectorization,
    model_path='result/restore_diacritic_cont.keras'
)

transformer.fit(train_ds, epochs=50, validation_data=val_ds)
```
