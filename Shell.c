#include <stdio.h>
#include <stdlib.h>



struct word_list {
	char *word;
	struct word_list* next;
	struct word_list* previous;
};

char *GetLineUnlim(){
	char c;
	int buff_size = 10, i =-1, n=2;
	char *line = (char*) malloc(buff_size *sizeof(char));
	char *p = line;
	while(1){
		i++;
		if (i == 10){
			line = realloc(line, n*buff_size);
			i = 0;
			n++;
		}
		c = getchar();
		if (c == '\n' || c == EOF){
			*p = '\n';
			return line;
		}	
		else {
			*p = c;
			p++;
		}
	}
}

char *line;

char* read_word()
{
	char c;
	int buff_size = 10, i=-1, n=2;
	char *word = (char*) malloc(buff_size);
	char *p = word;
	int in_word = 0, in_quotes = 0; 	
	while(1){
		i++; 
		if (i == 10){
			word = realloc(word, n*buff_size);
			i = 0;
			n++;
		}
		c = *line;
		if(isspace(c)){
			if (c == '\n'|| c == EOF){
				*p = '\n';
				return word;
				
			}
			if(!in_quotes){
				if(in_word){
					in_word--;
					*p = '\0';
					return word;
				}
				else {}
			}
			else
				goto write;
		}
		else{
			if(!in_word)
				in_word++;
			if(c == '\"')
				if(in_quotes){
					in_quotes--;
					line++;
					continue;
				}
				else{
					in_quotes++;
					line++;
					continue;
				}
			write:
			*p = c;
			p++;
		}
		line++;
			
	}
}


struct word_list* addword (char*word){
	struct word_list *list = (struct word_list*) malloc (sizeof(struct word_list));
	(*list).word = word;
	(*list).next = NULL;
	list->next = NULL;
		return list;
}


void PrintWord(char* word){
	while ((*word != '\0') && (*word != '\n')){
		printf("%c", *word);
		word++;
	}
	printf("\n");
}

void PrintList(struct word_list *list){
	struct word_list *head;
	head = list;
	while (list != NULL){
		PrintWord((*list).word);
		list = (*list).next;
	}
	list = head;	
}

void FreeList(struct word_list *list){
	struct word_list *next;
	while(list->next !=NULL){
		next = list->next;
		free(list);
		list = next;
	}
	free(list);
}

int main(){
	struct word_list *list;
	list = NULL;
	line = GetLineUnlim();
	char *header = line;
	struct word_list *head;
	char *word;
	do {
		word = read_word();
		if (list == NULL){
			list = addword(word);
			head = list;
		}
		else{
			(*list).next = addword(word);
			list->next->previous = list;
			list = (*list).next;
		}
	}while(*line != '\n');
	list = head;

	PrintList(list);
	FreeList(list);
	line = header;
	free(line);

return 0;
}
