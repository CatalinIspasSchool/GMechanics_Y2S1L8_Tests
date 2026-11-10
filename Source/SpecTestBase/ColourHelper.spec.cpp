#include "Misc/AutomationTest.h"
#include "ColourHelper.h"

BEGIN_DEFINE_SPEC(ColourHelperSpec,
	"CMP302 Lab 8",
	EAutomationTestFlags::ProductFilter |
	EAutomationTestFlags_ApplicationContextMask)

	END_DEFINE_SPEC(ColourHelperSpec)

	void ColourHelperSpec::Define()
{
	Describe("ColourHelper: RGB2BGR", [this]()
		{
			It("should return an FLinearColor with the Red & Blue components swapped",
				[this]()
				{
					FLinearColor InputCol(1.0f, 0.0f, 0.0f, 1.0f);

					FLinearColor OutputCol = ColourHelper::RGB2BGR(InputCol);

					TestTrue("RGB2BGR",
						((OutputCol.R == InputCol.B) &&
							(OutputCol.B == InputCol.R)));
				});
		});
}