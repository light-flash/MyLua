
#include <windows.h>

#include "..\luasrc\lua.hpp"

static int util_sums(lua_State *L) {
	int number = lua_gettop(L);//��ȡջ���ϵ�Ԫ�ظ���

	lua_Number sum = 0.0;//�ۼƲ�����
	for (int i = 1; i <= number; ++i) {
		if (!lua_isnumber(L, i)) {//���
			lua_pushliteral(L, "��������");
			lua_error(L);
		}
		sum += lua_tonumber(L, i);
	}

	lua_pushnumber(L, sum);
	lua_pushstring(L, "���ײ˵�С����");

	return 2;//����ֵ�ĸ���
}

static const luaL_Reg util[] = {
	{"xqlSums", util_sums},
	{NULL, NULL}
};

extern "C" __declspec(dllexport)
int luaopen_MyUtil(lua_State *L) {
	luaL_newlib(L, util);
	return 1;
}