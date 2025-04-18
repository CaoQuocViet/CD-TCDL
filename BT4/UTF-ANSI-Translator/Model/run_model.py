from transformers import AutoTokenizer, AutoModelForTokenClassification
import torch
import numpy as np

# Hàm tải mô hình
def load_trained_transformer_model():
    model_path = "."  # Vì mô hình ở thư mục hiện tại
    tokenizer = AutoTokenizer.from_pretrained(model_path, add_prefix_space=True)
    model = AutoModelForTokenClassification.from_pretrained(model_path)
    return model, tokenizer

# Tải mô hình
model, tokenizer = load_trained_transformer_model()

# Thiết lập thiết bị (CPU hoặc GPU)
device = torch.device("cuda") if torch.cuda.is_available() else torch.device("cpu")
model.to(device)

# Chuyển sang chế độ đánh giá
model.eval()

# Hàm thêm dấu
def insert_accents(text, model, tokenizer):
    our_tokens = text.strip().split()

    # Tokenizer có thể chia nhỏ các token của chúng ta
    inputs = tokenizer(our_tokens,
                      is_split_into_words=True,
                      truncation=True,
                      padding=True,
                      return_tensors="pt"
                     )
    input_ids = inputs['input_ids']
    tokens = tokenizer.convert_ids_to_tokens(input_ids[0])
    tokens = tokens[1:-1]  # Bỏ token đánh dấu đầu và cuối

    with torch.no_grad():
        inputs.to(device)
        outputs = model(**inputs)

    predictions = outputs["logits"].cpu().numpy()
    predictions = np.argmax(predictions, axis=2)

    # Loại bỏ đầu ra ở chỉ mục 0 và chỉ mục cuối cùng
    predictions = predictions[0][1:-1]

    assert len(tokens) == len(predictions)

    return tokens, predictions

# Tải danh sách thẻ
def _load_tags_set(fpath):
    labels = []
    with open(fpath, 'r', encoding='utf-8') as f:
        for line in f:
            line = line.strip()
            if line:
                labels.append(line)
    return labels

label_list = _load_tags_set("./selected_tags_names.txt")
assert len(label_list) == 528, f"Expect 528 tags, got {len(label_list)}"

# Hàm gộp tokens và dự đoán
TOKENIZER_WORD_PREFIX = "▁"
def merge_tokens_and_preds(tokens, predictions): 
    merged_tokens_preds = []
    i = 0
    while i < len(tokens):
        tok = tokens[i]
        label_indexes = set([predictions[i]])
        if tok.startswith(TOKENIZER_WORD_PREFIX): # Bắt đầu một từ mới
            tok_no_prefix = tok[len(TOKENIZER_WORD_PREFIX):]
            cur_word_toks = [tok_no_prefix]
            # Kiểm tra xem các token tiếp theo có phải là một phần của từ này không
            j = i + 1
            while j < len(tokens):
                if not tokens[j].startswith(TOKENIZER_WORD_PREFIX):
                    cur_word_toks.append(tokens[j])
                    label_indexes.add(predictions[j])
                    j += 1
                else:
                    break
            cur_word = ''.join(cur_word_toks)
            merged_tokens_preds.append((cur_word, label_indexes))
            i = j
        else:
            merged_tokens_preds.append((tok, label_indexes))
            i += 1

    return merged_tokens_preds

# Hàm nhận từ có dấu
def get_accented_words(merged_tokens_preds, label_list):
    accented_words = []
    for word_raw, label_indexes in merged_tokens_preds:
        # Sử dụng nhãn đầu tiên làm thay đổi word_raw
        for label_index in label_indexes:
            tag_name = label_list[int(label_index)]
            raw, vowel = tag_name.split("-")
            if raw and raw in word_raw:
                word_accented = word_raw.replace(raw, vowel)
                break
        else:
            word_accented = word_raw

        accented_words.append(word_accented)

    return accented_words

# Hàm chính để thêm dấu vào văn bản
def add_accent(text):
    tokens, predictions = insert_accents(text, model, tokenizer)
    merged_tokens_preds = merge_tokens_and_preds(tokens, predictions)
    accented_words = get_accented_words(merged_tokens_preds, label_list)
    return ' '.join(accented_words)

# Thử nghiệm
if __name__ == "__main__":
    while True:
        text = input("Nhập văn bản không dấu (nhập 'exit' để thoát): ")
        if text.lower() == 'exit':
            break
        result = add_accent(text)
        print(f"Kết quả: {result}")
