cardList=[]
def menu():
    print("-----------------")
    print("|  名片管理系统    |")
    print("|  1.添加名片     |")
    print("|  2.删除名片     |")
    print("|  3.修改名片     |")
    print("|  4.查询名片     |")
    print("|  5.显示全部     |")
    print("|  6.退出系统     |")
    print("-----------------")

def show():
    print("名片合集：")
    for temp in cardList:
        print("姓名：%c" % temp["name"], "  ", end='')
        print("学号：%c" % temp["number"], "  ", end='')
        print("联系方式：%c" % temp["tel"])

def add():
    name = input("请输入姓名：")
    number = input("请输入学号：")
    tel = input("请输入联系方式：")
    card={"name":name,"number":number,"tel":tel}
    cardList.append(card)

def delete():
    c = input("请输入要删除的名片的名字：")
    for n in cardList:
        if c == n["name"]:
            cardList.remove(n)

def change():
    c = input("请输入要修改的名片的名字：")
    for n in cardList:
        if c == n["name"]:
            new_name = input("请输入新姓名：")
            new_number = input("请输入新学号：")
            new_tel = input("请输入新联系方式：")
            n["name"] = new_name
            n["number"] = new_number
            n["tel"] = new_tel

def search():
    c = input("请输入要查询的名字：")
    for n in cardList:
        if c == n["name"]:
            print("查询结果如下：")
            print("姓名：%c" % n["name"], "  ", end='')
            print("学号：%c" % n["number"], "  ", end='')
            print("联系方式：%c" % n["tel"])
        else:
            print("查无此人！")

if __name__ == '__main__':
    while True:
        menu()
        choice=input("请选择操作：")
        a=int(choice)
        if a in [1,2,3,4,5,6]:
            if a==1:
                add()
            elif a == 2:
                delete()
            elif a == 3:
                change()
            elif a == 4:
                search()
            elif a==5:
                show()
            elif a==6:
                break
            else:
                print("操作无效！")



