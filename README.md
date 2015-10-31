# kmc89 c89-compiler
ANSI C89のコンパイラ

[![Build Status](https://travis-ci.org/kmc-jp/c89-compiler.svg?branch=master)](https://travis-ci.org/kmc-jp/c89-compiler)

## コンパイラのテスト用のCのソースコードの書き方

コンパイラのテストのソースコードは現在stage1/stage2の二種類に分類されています。

- stage1: プリプロセッサや標準ライブラリを用いないソースコード
  - グローバル関数として`void print(const char *)`, `void print_num(int)`の2つが利用可能です。
- stage2: プリプロセッサや標準ライブラリを用いたソースコード

`tests/stage1`, `tests/stage2`以下においたC言語のソースファイル(\*.c)がそれぞれstage1, stage2のテストに使われます。

書き方の例はそれぞれのディレクトリの中の`fibonacci.c`などを参照してください。

ソースコードが書けたらこのディレクトリで`$ make test`するとコンパイルが行われ、ソースコードのあるディレクトリに`hoge.c`なら`hoge.out`という名前で実行ファイルが生成されるので、正しい実行結果が得られるか確かめてください。

基本的なコードから重箱の隅をつつくようなコードまでどんどん書きましょう。
