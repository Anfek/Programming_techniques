from PIL import Image, ImageColor
from PIL import ImageDraw

from PIL import Image, ImageTk
import tkinter as tk

width = 400
height = 300

image = Image.new("RGB", (width, height))
draw = ImageDraw.Draw(image)

# Заполним все изображение белым цветом
draw.rectangle((0, 0, width-1, height-1), fill=ImageColor.getrgb("white"), outline=ImageColor.getrgb("grey"))


def function1(x):
    return 5 * (x ** 2) + x ** 3 - x ** 4


class Point:  # создал класс для удобства
    def __init__(self, x, y):
        self.x = x
        self.y = y


# задаем область значений функции

start_x = -4
end_x = 4
start_y = -15
end_y = 15

points = []

x = start_x
step_x = 0.1

while x <= end_x:  # проходим по всей ширине
    y = function1(x)  # вычисляем значение функции для текущего значения x
    points.append(Point(x, y))  # добавляем эту точки в список точек
    x += step_x  # увеличиваем x


# И так у нас есть список точек функции в заданном регионе. Как таблица значений функции в школе.
# Все точки в системе координат функции.

def convert(point):
    # Напишем функцию которая будет конвертировать точку в системе координат функции, в нашу систему координат
    # У нас вся ширина 400, а графика функции в нашей области от -4 до 4 - 8 единиц
    # Поэтому вычислим масштаб по x и по y: т.е. во сколько раз ширина изображения больше ширины графика

    scale_x = width / (end_x - start_x)
    scale_y = height / (end_y - start_y)

    # Зная мастшаб, мы вычисляем координаты в нашей системе координат для текущей точки
    local_x = point.x * scale_x
    local_y = point.y * scale_y

    # Помните что, у нас центры разные? Перемещаем центр точек Так как начало графика по x -4, мы должны
    # умножить -4 на машстаб и сдвинуть точки на 4 значения правее (поэтому с минусом).
    # и точно также сдвигаем по y
    local_x = (-start_x * scale_x) + local_x
    local_y = (-start_y * scale_y) + local_y

    # Создаем новую точку в нашей системе координат. И переворичваем Y. Сами догадайтесь почему.
    return Point(local_x, height - local_y)

# рисуем оси координат
start_hor = convert(Point(start_x, 0))
end_hor = convert(Point(end_x, 0))
draw.line((start_hor.x, start_hor.y, end_hor.x, end_hor.y), fill=ImageColor.getrgb("grey"))

start_ver = convert(Point(0, start_y))
end_ver = convert(Point(0, end_y))
draw.line((start_ver.x, start_ver.y, end_ver.x, end_ver.y), fill=ImageColor.getrgb("grey"))

# рисуем на экране все точки.

last_point = convert(points[0])
for point in points:
    current_point = convert(point)
    draw.line((last_point.x, last_point.y, current_point.x, current_point.y), fill=ImageColor.getrgb("blue"))
    last_point = current_point


window = tk.Tk()
tk_image = ImageTk.PhotoImage(image)
tk.Label(window, image=tk_image).pack()
window.mainloop()

#image.save("graphic.png", "PNG")
#image.show("graphic.png")