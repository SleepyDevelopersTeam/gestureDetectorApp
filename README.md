# gestureDetectorApp

**IMPORTANT**: do not forget to create `libs.pri` file where to include your OpenCV libs.
It's included in main `.pro` file, so nothing will build without it.

## План на уир:

**12.10.16** Составление и реализация основной структуры системы

**15.10.16** Определяем лицо человека и руки

**19.10.16** Оформление документации

**22.10.16** Выделение ключевых особенностей в движении рук

**26.10.16** Состовление гистограммы силуета человека

**29.10.16** Выделение ключевых особенностей гистограмм

**2.11.16** 

**5.11.16** 

**9.11.16** 

**12.11.16** 

**16.11.16** Действующий алгоритм определяющий несколько разных жестов

**19.11.16** 

**23.11.16** 

**26.11.16** Работа алгоритма в составе системы

**30.11.16**

**3.12.16** 

***

# Алгоритм

---

Алгоритм - является ядром системы, дальнейшая разработка, это его обертка.
На первоночальном этапе это главная цель.

### Детектирование человека 

На первоначальный этап выносится изучение и разработка адаптивного детектирования человека на изображении.
Основной алгоритм заключается в поиске человека по цвету кожи. При оценке качества работы данного алгоритма (возможный вариант создания адаптивного алгоритма), в плохих результатах возможен вызов другого алгоритма.

### Построение компонент связности человека

После детектирования человек, определяем компоненты связности его секлета. Самаое важное определить положение рук, ног и головы на изображании.


### Нахождение перемещения

Между несколькими кадрами строим поток (оптический) в котором следим за областями, где находились наши компоненты связности. Тоесть мерджим изображения, следя за нашими областями. После этого мы можем построить вектор перемещения каждой из компонент


### Определение жеста 

Посдле предыдущих жестов, мы знаем куда переместилась каждая из компонент связности, и тем самым мы сможем понять что жест совершен и даже его задать. 

В дальнейшем возможно написание класификатора, или нейронной сети для классивикации жеста.
