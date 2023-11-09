/*
test case
INPUT:
    infomation:
        ・基本文法
            arg[0] == "<"のとき
                arg[1]: file
                arg[2]: cmd
                ただし
                    < file1 cat file2とするとcat file2が出力される
            arg[1] == "<"のとき
                arg[0]: cmd
                arg[2]: file
                
        ・ファイル判定
            arg[1] == "<"の時
                cmd < file1 file2　 ... fileN
            を実行すると[fileN]に対して[cmd]を実行する。対して、
            arg[0] == "<"の時に
                < file1 file2 ...fileN cmd
            とすると、[file1]に対して[file2というcmd]を実行しようとする。

        仮説:
            error_messageの判定について
                <の位置が基準となって
                    [    cmd    ] < [   file   ]
                    < [   file   ] [   cmd   ]
                という判定になり、それを元にerror messageが作成されている
                例えば
                    file cmd <
                を実行すると[-bash: syntax error near unexpected token `newline']が出力されるように、
                    「file cmd」がcmdとして判定され、cmdが正しいか否かよりも先にfileの欠損を指摘される
            → error_messageの判定はOPERATORのidxから条件分岐させると良さそう
    policy:
        ・cmdの判定を曖昧にする
            cat cat < fileに対して
                cat: cat: No such file or directory
            というエラーメッセージがでることから　、２つ目のcatはcatコマンド内で判定されていることがわかり、redirectionのステップでは[cat cat]をコマンドとして処理する
OUTPUT:

HERE_DOC:
    infomation:
        arg[0] == "<<"のとき
            arg[1]: DELIMITER
            arg[2]: cmd
            arg[i >= 3]: cmdのoption
        arg[1] == "<<"のとき
            arg[0]: cmd
            arg[2]: DELIMITERとして扱われる

    input possible case:
        argc = 2:
            << DELIMITER
            << cmd 
        argc = 3:
            << DELIMITER cmd
            << DELIMITER << [-bash: syntax error near unexpected token `newline']
            cmd << DELIMITER 
            DELIMTIER << cmd [-bash: DELIMITER: command not found]
    input impossible case:
        argc = 1:
            << [-bash: syntax error near unexpected token `newline']
        argc = 2:
            cmd << [-bash: syntax error near unexpected token `newline']
            DELIMITER << [-bash: syntax error near unexpected token `newline']
            << << [-bash: syntax error near unexpected token `<<']
                notice: arg[1]の<<は <, >, >> でも同じerrorになる。他のspecial charは未確認
                        a<<aやa<だとinput possibleになり、特殊な挙動になる
        argc = 3:
            DELIMITER cmd << [-bash: syntax error near unexpected token `newline']
            cmd DELIMTER << [-bash: syntax error near unexpected token `newline']
            << << cmd [-bash: syntax error near unexpected token `<<']
    

APPEND:

*/