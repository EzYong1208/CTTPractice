// Copyright Epic Games, Inc. All Rights Reserved.


#include "CTTUICommonResource.h"


UTexture2D* UCTTUICommonResource::GetNumberTexture(ECTTNumberImageType NumberImageType, int32 Number) const
{
	const FCTTNumberImageList* NumberImageListPtr = NumberImageMap.Find(NumberImageType);

	if (nullptr == NumberImageListPtr)
	{
		return nullptr;
	}

	if (!NumberImageListPtr->Images.IsValidIndex(Number))
	{
		return nullptr;
	}

	return NumberImageListPtr->Images[Number];
}
