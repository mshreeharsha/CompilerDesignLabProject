%%
\n {line_num++;}

auto|const|default|do|enum|extern|goto|inline|register|restrict|short|signed|sizeof|static|typedef|void|volatile {fprintf(yyout,"%30s \t--->\tKEYWORD \t%24d\n", yytext,line_num);};


[-]?[0-9]+\.[0-9]{1,6} {
    processToken(yytext,"Floating-Point Constants",line_num);
    fprintf(yyout,"%30s \t--->\tFLOATING-POINT CONSTANT \t%30d\n", yytext,line_num);
}

\|\||\&\& {fprintf(yyout,"%30s \t--->\tLOGICAL OPERATOR \t%16d\n", yytext,line_num+1);}

\||\&|\^|\! {fprintf(yyout,"%30s \t--->\tBIT-WISE OPERATOR \t%14d\n", yytext,line_num+1);}

==|<=|>=|!=|<|> {fprintf(yyout,"%30s \t--->\tRELATIONAL OPERATOR \t%12d\n", yytext,line_num+1);}

(\/\*)(.|\n)+? {
    int k  = 2;
    int err = 0;
    int found  = 0;
    while(k<yyleng){
        if(yytext[k]=='/' && (k+1)<yyleng && yytext[k+1]=='*'){
            err = 1;
        }
        if(yytext[k]=='*' && (k+1)<yyleng && yytext[k+1]=='/'){
            found = 1;
            break;
        }
        ++k;
    }
    if(err == 0 && found==1){
        int kk  = k;
        kk+=2;
        for (int i = 0; i < kk; i++) {
            if (yytext[i] == '\n') {
                ++line_num;
            } else if (yytext[i] != ' ') {
                int j = i;
                char temp[100];
                int temp_index = 0;
                while (j < kk && yytext[j] != '\n' && yytext[j] != ' ') {
                    temp[temp_index] = yytext[j];
                    temp_index++;
                    j++;
                }
                temp[temp_index] = '\0';
                fprintf(yyout, "%30s \t--->\tMULTILINE COMMENT \t%14d\n", temp, line_num);
                i = j - 1;
            }   
        }
    }
    else if(err == 1){
        printf("\n\nERROR : Invalid Comment -> nested comments are not supported */ '%s' \nline no : %d", yytext, line_num);
    }
    else{
        printf("\n\nERROR : Invalid Comment -> does not end with */ '%s' \nline no : %d", yytext, line_num);
    }
    for(int i = yyleng-1;i>k+1;--i){
            unput(yytext[i]);
    }
}

.|\n ;
%%
