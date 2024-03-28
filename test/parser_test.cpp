#include "ast.h"
#include "parser.h"

using namespace yapvm::ast;
using namespace yapvm;
using namespace yapvm::parser;


int main() {
    std::string test_data = "Module(body=[Import(names=[alias(name='logging')]), Import(names=[alias(name='threading')]), Import(names=[alias(name='time')]), FunctionDef(name='thread_function', args=arguments(posonlyargs=[], args=[arg(arg='name')], kwonlyargs=[], kw_defaults=[], defaults=[]), body=[Expr(value=Call(func=Attribute(value=Name(id='logging', ctx=Load()), attr='info', ctx=Load()), args=[Constant(value='Thread %s: starting'), Name(id='name', ctx=Load())], keywords=[])), Expr(value=Call(func=Attribute(value=Name(id='time', ctx=Load()), attr='sleep', ctx=Load()), args=[Constant(value=2)], keywords=[])), Expr(value=Call(func=Attribute(value=Name(id='logging', ctx=Load()), attr='info', ctx=Load()), args=[Constant(value='Thread %s: finishing'), Name(id='name', ctx=Load())], keywords=[]))], decorator_list=[], type_params=[]), If(test=Compare(left=Name(id='__name__', ctx=Load()), ops=[Eq()], comparators=[Constant(value='__main__')]), body=[Assign(targets=[Name(id='format', ctx=Store())], value=Constant(value='%(asctime)s: %(message)s')), Expr(value=Call(func=Attribute(value=Name(id='logging', ctx=Load()), attr='basicConfig', ctx=Load()), args=[], keywords=[keyword(arg='format', value=Name(id='format', ctx=Load())), keyword(arg='level', value=Attribute(value=Name(id='logging', ctx=Load()), attr='INFO', ctx=Load())), keyword(arg='datefmt', value=Constant(value='%H:%M:%S'))])), Expr(value=Call(func=Attribute(value=Name(id='logging', ctx=Load()), attr='info', ctx=Load()), args=[Constant(value='Main    : before creating thread')], keywords=[])), Assign(targets=[Name(id='x', ctx=Store())], value=Call(func=Attribute(value=Name(id='threading', ctx=Load()), attr='Thread', ctx=Load()), args=[], keywords=[keyword(arg='target', value=Name(id='thread_function', ctx=Load())), keyword(arg='args', value=Tuple(elts=[Constant(value=1)], ctx=Load()))])), Expr(value=Call(func=Attribute(value=Name(id='logging', ctx=Load()), attr='info', ctx=Load()), args=[Constant(value='Main    : before running thread')], keywords=[])), Expr(value=Call(func=Attribute(value=Name(id='x', ctx=Load()), attr='start', ctx=Load()), args=[], keywords=[])), Expr(value=Call(func=Attribute(value=Name(id='logging', ctx=Load()), attr='info', ctx=Load()), args=[Constant(value='Main    : wait for the thread to finish')], keywords=[])), Expr(value=Call(func=Attribute(value=Name(id='logging', ctx=Load()), attr='info', ctx=Load()), args=[Constant(value='Main    : all done')], keywords=[]))], orelse=[])], type_ignores=[])";
    scoped_ptr<Module> ast = generate_ast(test_data);
}