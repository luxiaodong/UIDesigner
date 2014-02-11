
uiBuilder = {};

local default_fontName = "Thonburi";

-- if filePath is res/lua/uidata/test.lua.  fileName is "test".
function uiBuilder.loadUILayer(fileName)
	local layer, name = uiBuilder.loadUIData(fileName);
	ui[fileName] = {};
	ui[fileName][name] = layer;
end

function uiBuilder.loadUIData(fileName)
	if uidata[fileName] ~= nil then
		for k,v in pairs(uidata[fileName]) do
			return uiBuilder.loadSingleUI(v), k;
		end
	else
		print("uiBuilder load uidata failed. not exist with file --> "..fileName);
	end
end

function uiBuilder.loadSingleUI(property)
	local classType = property["classType"];
	local parentNode = nil;

	if classType == "CCSprite" then
		parentNode = uiBuilder.createCCSprite(property);
	elseif classType == "CCLabelTTF" then
		parentNode = uiBuilder.createCCLabelTTF(property);
	elseif classType == "CCLayer" then
		parentNode = uiBuilder.createCCLayer(property);
	elseif classType == "CCContainerLayer" then
		parentNode = uiBuilder.createCCContainerLayer(property);
	elseif classType == "CCMenuItemImage" then
		parentNode = uiBuilder.createCCMenuItemImage(property);
	elseif classType == "CCScale9Sprite" then
		parentNode = uiBuilder.createCCScale9Sprite(property);
	elseif classType == "CCLabelAtlas" then
		parentNode = uiBuilder.createCCLabelAtlas(property);
	elseif classType == "CCProgressTimer" then
		parentNode = uiBuilder.createCCProgressTimer(property);
	elseif classType == "CCScrollView" then
		parentNode = uiBuilder.createCCScrollView(property);
	end

	if parentNode ~= nil then
		if property["children"] ~= nil then
			local parentSize = {};
			parentSize.width = property["width"];
			parentSize.height = property["height"];
			parentNode.children = {};

			local menuNode = nil;

			for k,v in pairs( property["children"] ) do
				local sonNode = uiBuilder.loadSingleUI(v);
				local x,y = uiBuilder.calculateCoordinates(v, parentSize);
				sonNode:setPosition(ccp(x,y));

				if v["classType"] == "CCMenuItemImage" then --按钮要多插入一个CCMenu
					if menuNode == nil then
						menuNode = CCMenu:create();
						menuNode:setPosition(ccp(0,0));
						parentNode:addChild(menuNode, v["z"]);
					end

					menuNode:addChild(sonNode, v["z"], v["tag"]);
				else
					parentNode:addChild(sonNode, v["z"], v["tag"]);
				end

				parentNode.children[k] = sonNode;
			end
		end

		if property["isVisible"] then
			parentNode:setVisible(false);
		end
	else
		print(classType);
	end

	return parentNode;
end

function uiBuilder.createCCSprite(property)
	local temp = CCSprite:create( property["filePath"] );

	if property["scaleX"] ~= nil then
		temp:setScaleX( property["scaleX"] );
	end

	if property["scaleY"] ~= nil then
		temp:setScaleY( property["scaleY"] );
	end

	return temp;
end

function uiBuilder.createCCLabelTTF(property)
	local fontName = property["fontName"];
	if fontName == nil then
		fontName = default_fontName;
	end

	local text = "";
	if property["text"] ~= nil then
		text = property["text"];
	end

	local temp = CCLabelTTF:create( text, fontName, property["pointSize"]);

	local r = property["color_r"];
	local g = property["color_g"];
	local b = property["color_b"];

	if r ~= nil and g ~= nil and b ~= nil then
		temp:setColor(ccc3(r,g,b));
	end

	local dimensionWith = property["dimensionWith"];
	local dimensionHeight = property["dimensionHeight"];

	if dimensionWith ~= nil then
		temp:setDimensions(CCSizeMake(dimensionWith, dimensionHeight));

		local alignment = property["horizontalAlignment"];
		
		if alignment ~= nil then
			temp:setHorizontalAlignment(alignment);
		end
		
		alignmen = property["verticalAlignment"];

		if alignment ~= nil then
			temp:setVerticalAlignment(alignmen);
		end
	end

	return temp;
end

function uiBuilder.createCCLayer(property)
	local temp = CCLayer:create();
	return temp;
end

function uiBuilder.createCCContainerLayer(property)
	local filePath = property["containerConfigFilePath"];
	local fileName = uiBuilder.getFileName(filePath);
	filePath = string.sub( filePath, 1, string.len(filePath) - 4);
	require(filePath);
	return uiBuilder.loadUIData(fileName);
end

function uiBuilder.createCCMenuItemImage(property)
	local temp = nil;
	local image_n = property["image_n"];
	local image_h = property["image_h"];
	local image_d = property["image_d"];

	if image_n ~= nil then
		if image_h ~= nil then 
			if image_d ~= nil then
				temp = CCMenuItemImage:create(image_n, image_h, image_d);
			else
				temp = CCMenuItemImage:create(image_n, image_h);
			end
		else
			temp = CCMenuItemImage:create(image_n, image_n);
		end
	end

	return temp;
end

function uiBuilder.calculateCoordinates(property, winSize)
	local x = property["x"];
	local y = property["y"];
	return x,y;
end

function uiBuilder.createCCScale9Sprite(property)
	local filePath = property["filePath"];
	local r_x = property["insets_x"];
	local r_y = property["insets_y"];
	local r_w = property["insets_w"];
	local r_h = property["insets_h"];
	local temp = CCScale9Sprite:create( filePath, CCRectMake(r_x, r_y, r_w, r_h) );
	local s_w = property["perferred_w"];
	local s_h = property["perferred_h"];
	temp:setPreferredSize(CCSizeMake(s_w, s_h));
	return temp;
end

function uiBuilder.createCCProgressTimer(property)
	local sprite = CCSprite:create( property["filePath"] );
	local temp = CCProgressTimer:create(sprite);
    temp:setType( property["progressTimerType"] );

    local direction = tonumber(property["direction"]);

    if direction == 0 then			--从左到右
    	temp:setMidpoint(ccp(0, 0.5));  
		temp:setBarChangeRate(ccp(1, 0)); 
    elseif direction == 1 then		--从右到左
    	temp:setMidpoint(ccp(1, 0.5));  
		temp:setBarChangeRate(ccp(1, 0)); 
    elseif direction == 2 then		--从下到上
    	temp:setMidpoint(ccp(0.5, 0));  
		temp:setBarChangeRate(ccp(0, 1)); 
    elseif direction == 3 then		--从上到下
    	temp:setMidpoint(ccp(0.5, 1));  
		temp:setBarChangeRate(ccp(0, 1)); 
    end

    temp:setPercentage( property["percentage"]*100 );
    return temp;
end

function uiBuilder.createCCLabelAtlas(property)
	local text = property["text"];
	local filePath = property["filePath"];
	local width = property["elementWidth"];
	local height = property["elementHeight"];
	local startChar = property["startChar"];
	local temp = CCLabelAtlas:create(text, filePath, width, height, startChar);
	temp:setAnchorPoint(ccp(0.5,0.5));
	return temp;
end

function uiBuilder.createCCScrollView(property)
	local width = property["contentWidth"];
	local height = property["contentHeight"];
	local temp = CCScrollView:create(CCSizeMake(width, height));
	local direction = property["direction"];
	temp:setDirection( direction );
	
	local isDynamically = property["isDynamicallyGenerated"];
	if tonumber(isDynamically) == 0 then
		if property["containerConfigFilePath"] ~= nil then
			local layer = CCLayer:create();
			local count = property["count"];
			local fileName = uiBuilder.getFileName(property["containerConfigFilePath"]);
			local itemName = nil;

			for i=1,count do
				local item , name = uiBuilder.createCCContainerLayer(property);
				itemName = name;

				if tonumber(direction) == kCCScrollViewDirectionHorizontal then
					local x = tonumber(property["offsetX"]) + (i - 1)*tonumber(uidata[fileName][name]["width"]) + tonumber(property["spaceWidth"]);
					item:setPosition(ccp( x, property["offsetY"]));
				elseif tonumber(direction) == kCCScrollViewDirectionVertical then
					local y = tonumber(property["offsetY"]) + (i - 1)*tonumber(uidata[fileName][name]["height"]) + tonumber(property["spaceHeight"]);
					item:setPosition(ccp( property["offsetX"], y));
				end

				item:setAnchorPoint(ccp(0,0));
				layer:addChild(item, property["z"], property["tag"]);
				temp["item_"..i] = item;
			end

			temp["layer"] = layer;
			temp:setContainer(layer);
			if tonumber(direction) == kCCScrollViewDirectionHorizontal then
				temp:setContentSize(CCSizeMake(2*property["offsetX"] + count*uidata[fileName][itemName]["width"] + (count - 1)*property["spaceWidth"], height));
			elseif tonumber(direction) == kCCScrollViewDirectionVertical then
				temp:setContentSize(CCSizeMake(width, 2*property["offsetY"] + count*uidata[fileName][itemName]["height"] + (count - 1)*property["spaceHeight"] ));
			end
		else
			print("load config file failed in ccscrollview. nil.");
		end
	end

	return temp;
end


function uiBuilder.getFileName(filePath)
	local list = tool.split(filePath,"/");
	local fileName = list[ #list ];
	fileName = string.sub( fileName, 1, string.len(fileName) - 4);
	return fileName;
end

