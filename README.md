# Dining philosophers problem

![image](https://github.com/user-attachments/assets/96c6cce8-2c26-48b5-b2cf-5d503865dfd9)
from wiki

## `Grade: 125/100`
セマフォを使ったボーナスにも対応．正直ボーナスの方が簡単だった．


データ競合が起きないようにクリティカルセクション内の変数は，ロックを作っている．構造体を新たに作成し，データ型で判断できるように工夫した．
デッドロック自体は哲学者のIDの偶奇で取る順番を変えれば防げるが，飢餓(starvation)を防ぐには何かしらの機構が必要．sleepを使った制御も考えたが，キューを使うのが一番自然な気がしたのでこれにした．
はじめに奇数の哲学者を入れ，次に偶数の哲学者を並ばせた．
例) ./philo 5 610 200 200
  -> que: 2 4 1 3 5 

```
git clone --recursive https://github.com/cimura/philosopher.git
```
