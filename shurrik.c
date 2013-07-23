/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2010 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id: header 297205 2010-03-30 21:09:07Z johannes $ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_shurrik.h"

/* If you declare any globals in php_shurrik.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(shurrik)
*/

/* True global resources - no need for thread safety here */
static int le_shurrik;

/* {{{ shurrik_functions[]
 *
 * Every user visible function must have an entry in shurrik_functions[].
 */
zend_function_entry shurrik_functions[] = {
	PHP_FE(confirm_shurrik_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(say,NULL)
	PHP_FE(shurrik_work,NULL)
	PHP_FE(sample_array,NULL)
	PHP_FE(shurrik_get,NULL)
	{NULL, NULL, NULL}	/* Must be the last line in shurrik_functions[] */
};
/* }}} */

/* {{{ shurrik_module_entry
 */
zend_module_entry shurrik_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"shurrik",
	shurrik_functions,
	PHP_MINIT(shurrik),
	PHP_MSHUTDOWN(shurrik),
	PHP_RINIT(shurrik),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(shurrik),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(shurrik),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_SHURRIK
ZEND_GET_MODULE(shurrik)
#endif

//����hash��
int shurrik_hash_apply(zval **val, Bucket *bHead){
	Bucket *p;
	Bucket *head;
	zval **tmp;

	if(bHead == 0){
		return 1;
	}

	if(bHead == NULL){
	}else {
		p = bHead;
	}
	
	if(p == NULL){
		return 1;
	}

	php_printf("      ");
	php_printf("array(\n");
	
	while (p != NULL) {
			php_printf("            ");
			tmp = p->pData;

			if(p->nKeyLength){
				php_printf("%s=>",p->arKey);
			}else {
				php_printf("%ld=>",p->h);
			}
			if(Z_TYPE_PP(tmp) == IS_STRING){
				php_printf("%s\n",(**tmp).value.str.val);
			}
			if(Z_TYPE_PP(tmp) == IS_ARRAY){
				//php_printf("array()\n");
				//shurrik_apply_array(tmp);
				//php_printf("%p",ht->pListHead);
				//php_printf("%p",(**tmp).value.ht->pListHead->pListNext);
				if(p != (**tmp).value.ht->pListHead){
					shurrik_hash_apply(tmp,(**tmp).value.ht->pListHead);
				}else {
					php_printf("�ظ�����\n");
				}
			}
			p = p->pListNext;
		}
	php_printf("      );\n");
	return 1;

	/*Bucket *p;
	zval **tmp;
	
	if(bHead == NULL){
		if((**val).value.ht->pListHead == 0){
			return 1;
		}
		p = (**val).value.ht->pListHead->pListNext;
		if(p == 0){
			p = *(**val).value.ht->arBuckets;
		}
		if(p == 0){
			return 1;
		}
	}else {
		p = bHead;
	}

	if(p == NULL){
		 return 1;
	}
	php_printf("      ");
	php_printf("array(\n");
	while (p != NULL) {
			php_printf("            ");
			tmp = p->pData;

			if(p->nKeyLength){
				php_printf("%s=>",p->arKey);
			}else {
				php_printf("%ld=>",p->h);
			}
			if(Z_TYPE_PP(tmp) == IS_STRING){
				php_printf("%s\n",(**tmp).value.str.val);
			}
			if(Z_TYPE_PP(tmp) == IS_ARRAY){
				//php_printf("array()\n");
				//shurrik_apply_array(tmp);
				//php_printf("%p",ht->pListHead);
				//php_printf("%p",(**tmp).value.ht->pListHead->pListNext);
				shurrik_hash_apply(tmp,NULL);
			}
			p = p->pListNext;
		}
	php_printf("      );\n");
	return 1;
	*/
}







int shurrik_hash_apply_for_array(zval **val,int num_args,va_list args,zend_hash_key *hash_key)
{
    TSRMLS_FETCH();
	php_printf("      ");
    if (hash_key->nKeyLength)
    {
        //������ַ������͵�key
        PHPWRITE(hash_key->arKey, hash_key->nKeyLength);
    }	
    else
    {
        //������������͵�key
        php_printf("%ld", hash_key->h);
    }
	
	php_printf("=>");

	if(Z_TYPE_PP(val) == IS_ARRAY){
		//php_printf("%d",(**tmp).type);
		//zend_hash_apply((**val).value.ht,shurrik_hash_apply_for_zval, 0);
		/*if(Z_TYPE_PP(tmp) == IS_STRING){
			php_printf("%s",(**tmp).value.str.val);
		}*/
		Bucket *p;
		zval **tmp;

		p = (**val).value.ht->pListHead;
		if(p == NULL){
			return ZEND_HASH_APPLY_STOP; 
		}
		php_printf("array(\n");
		while (p != NULL) {
			php_printf("            ");
			tmp = p->pData;
			if(p->nKeyLength){
				php_printf("%s=>",p->arKey);
			}else {
				php_printf("%ld=>",p->h);
			}
			if(Z_TYPE_PP(tmp) == IS_STRING){
				php_printf("%s\n",(**tmp).value.str.val);
			}
			if(Z_TYPE_PP(tmp) == IS_ARRAY){
				//php_printf("array()\n");
				//shurrik_apply_array(tmp);
				//zend_hash_apply_with_arguments(((**tmp).value.ht)->pListHead->pData,shurrik_hash_apply_for_array, 0);
				//shurrik_hash_apply(tmp,p);
				//return shurrik_hash_apply_for_zval(tmp TSRMLS_CC);
			}
			p = p->pListNext;
		}
		php_printf("      );\n");
	}
	if(Z_TYPE_PP(val) == IS_STRING){
		php_printf("%s",(**val).value.str.val);
	}
	php_printf("\n");

    //���أ�����������һ����
    return ZEND_HASH_APPLY_KEEP;

}

int shurrik_hash_apply_for_zval(zval **val TSRMLS_DC)
{

    php_printf("      ");
	if(Z_TYPE_PP(val) == IS_ARRAY){
		//php_printf("%d",(**tmp).type);
		//zend_hash_apply((**val).value.ht,shurrik_hash_apply_for_zval, 0);
		/*if(Z_TYPE_PP(tmp) == IS_STRING){
			php_printf("%s",(**tmp).value.str.val);
		}*/
		Bucket *p;
		zval **tmp;

		p = (**val).value.ht->pListHead;
		if(p == NULL){
			return ZEND_HASH_APPLY_STOP; 
		}
		php_printf("array(\n");
		while (p != NULL) {
			php_printf("            ");
			tmp = p->pData;
			if(p->nKeyLength){
				php_printf("%s=>",p->arKey);
			}else {
				php_printf("%ld=>",p->h);
			}
			if(Z_TYPE_PP(tmp) == IS_STRING){
				php_printf("%s\n",(**tmp).value.str.val);
			}
			if(Z_TYPE_PP(tmp) == IS_ARRAY){
				//php_printf("array()\n");
				//shurrik_apply_array(tmp);
				return shurrik_hash_apply_for_zval(tmp TSRMLS_CC);
			}
			p = p->pListNext;
		}
		php_printf("      );\n");
	}
	if(Z_TYPE_PP(val) == IS_STRING){
		php_printf("%s",(**val).value.str.val);
	}
	php_printf("\n");

    //���أ�����������һ����
    return ZEND_HASH_APPLY_KEEP;
}

int shurrik_hash_apply_for_zval_and_key(zval **val,int num_args,va_list args,zend_hash_key *hash_key)
{
    TSRMLS_FETCH();

    if (hash_key->nKeyLength)
    {
		php_printf("$");
        //������ַ������͵�key
        PHPWRITE(hash_key->arKey, hash_key->nKeyLength);
		php_printf(" ");
		if(hash_key->nKeyLength >= 14){
			php_printf("\t");
		}else if(hash_key->nKeyLength >= 6 && hash_key->nKeyLength < 14){
			php_printf("\t\t");
		}else {
			php_printf("\t\t\t");
		}
    }	
    else
    {
        //������������͵�key
        php_printf("%ld", hash_key->h);
    }
	
	if(Z_TYPE_PP(val) == IS_STRING){
		php_printf("type:[string]\n");
		php_printf("%s",(**val).value.str.val);
	}
	if(Z_TYPE_PP(val) == IS_LONG){
		php_printf("type:[integer]\n");
		php_printf("%ld",(**val).value.lval);
	}
	if(Z_TYPE_PP(val) == IS_ARRAY){
		//convert_to_string(&(**val));
		//php_printf((**val).value.str.val);
		php_printf("type:[array]\n");
		//zend_hash_apply((**val).value.ht,shurrik_hash_apply_for_zval, 0);
		//zend_hash_apply_with_arguments((**val).value.ht,shurrik_hash_apply_for_array, 0);
		shurrik_hash_apply(val,(**val).value.ht->pListHead);
	}
	if(val == NULL){
		php_printf("type:[NULL]\n");
		php_printf("NULL");
	}

	php_printf("\n");

    return ZEND_HASH_APPLY_KEEP;
}

static void shurrik_get_value(){
	TSRMLS_FETCH();
    /*zval **fooval;

    if (zend_hash_find(
            EG(active_symbol_table), //��������ǵ�ַ��������ǲ���ȫ������������Ҫ&EG(symbol_table)
            "foo",
            sizeof("foo"),
            (void**)&fooval
        ) == SUCCESS
    )
    {
        php_printf("�ɹ�����$foo!");
    }
    else
    {
        php_printf("��ǰ���������޷�����$foo.");
    }*/
	zend_hash_apply_with_arguments(EG(active_symbol_table),shurrik_hash_apply_for_zval_and_key, 0);
}

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("shurrik.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_shurrik_globals, shurrik_globals)
    STD_PHP_INI_ENTRY("shurrik.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_shurrik_globals, shurrik_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_shurrik_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_shurrik_init_globals(zend_shurrik_globals *shurrik_globals)
{
	shurrik_globals->global_value = 0;
	shurrik_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(shurrik)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(shurrik)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(shurrik)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(shurrik)
{
	zend_hash_apply_with_arguments(EG(active_symbol_table),shurrik_hash_apply_for_zval_and_key, 0);
	//shurrik_hash_apply(active_symbol_table->);
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(shurrik)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "shurrik support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have succesfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_shurrik_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_shurrik_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "shurrik", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/

PHP_FUNCTION(say)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "\nShurrik say : \"%s\"\n", arg);
	RETURN_STRINGL(strg, len, 0);
}

PHP_FUNCTION(shurrik_work)
{
    char *arg = NULL;
	int arg_len, len;
	char *strg;
    int loop_expire = 500;
    int test = 1;
    
    for(;;){
        system("cls");
        shurrik_get_value();
        Sleep(loop_expire);        
    }

	RETURN_STRINGL(strg, len, 0);                    
}

ZEND_FUNCTION(sample_array)
{
    zval *subarray;

    array_init(return_value);

    /* Add some scalars */
    add_assoc_long(return_value, "life", 42);
    add_index_bool(return_value, 123, 1);
    add_next_index_double(return_value, 3.1415926535);

    /* Toss in a static string, dup'd by PHP */
    add_next_index_string(return_value, "Foo", 1);

    /* Now a manually dup'd string */
    add_next_index_string(return_value, estrdup("Bar"), 0);

    /* Create a subarray */
    MAKE_STD_ZVAL(subarray);
    array_init(subarray);

    /* Populate it with some numbers */
    add_next_index_long(subarray, 1);
    add_next_index_long(subarray, 20);
    add_next_index_long(subarray, 300);

    /* Place the subarray in the parent */
    add_index_zval(return_value, 444, subarray);
}

ZEND_FUNCTION(shurrik_get)
{
	/*
	zval *fooval;

    MAKE_STD_ZVAL(fooval);
    ZVAL_STRING(fooval, "bar", 1);
    ZEND_SET_SYMBOL( EG(active_symbol_table) ,  "foo" , fooval);
	*/
	//shurrik_get_value();

	//zend_hash_apply(EG(active_symbol_table),shurrik_hash_apply_for_zval TSRMLS_CC);
	zend_hash_apply_with_arguments(EG(active_symbol_table),shurrik_hash_apply_for_zval_and_key, 0);
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
