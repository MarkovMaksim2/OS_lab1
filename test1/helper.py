def convert_file_to_utf8(input_file, output_file):
    try:
        # Чтение файла в кодировке Windows-1251
        with open(input_file, 'r', encoding='windows-1251') as file:
            content = file.read()

        # Запись файла в кодировке UTF-8
        with open(output_file, 'w', encoding='utf-8') as file:
            file.write(content)

        print(f"Файл успешно преобразован и сохранён в {output_file}.")
    except Exception as e:
        print(f"Ошибка при преобразовании: {e}")

# Пример использования
input_file = 'D:\\studying\\OS\\lab1\\test1\\patriarh.txt'  # Замените на имя вашего файла
output_file = 'D:\\studying\\OS\\lab1\\test1\\patriarh_utf8.txt'  # Имя для сохранения нового файла

convert_file_to_utf8(input_file, output_file)