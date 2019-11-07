#!/usr/bin/python
#coding:utf-8

class Game(object):
    top_score = 0 #类属性
    top_time = 120*60 #类属性

    @staticmethod #静态方法
    def show_help():

    @classmethod #类方法
    def show_top_score(cls):

    def __init__(self,name):
        self.name = name  #实例属性

    def start_game(self):
        #实例方法
	
        Game.top_score = 999


#1.查看游戏帮助信息
Game.show_help()
#2.查看游戏最高分
Game.show_top_score()
#3.开始游戏
game = Game('小霸王')
game.start_game()
#4.游戏结束
game.show_top_score()
