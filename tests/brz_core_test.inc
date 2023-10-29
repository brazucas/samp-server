#include <tests\y_testing_mocks>
#include <brz_core>
#include <YSI_Core\y_testing>

@test(.group = "brz_core") ShouldReturnBRZVersion()
{
	ASSERT_EQ(BRZ_Core_GetBRZVersion(), 1);
}