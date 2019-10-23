CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 423;
	title = 42302;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActRegQInfo
			{
				cont = 42308;
				gtype = 0;
				area = 42301;
				goal = 42304;
				grade = 132203;
				rwd = 100;
				sort = 42305;
				stype = 2;
				taid = 1;
				title = 42302;
			}
			CDboTSActNPCConv
			{
				conv = 42309;
				ctype = 1;
				idx = 4261101;
				taid = 2;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 42307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSCheckLvl
			{
				maxlvl = 13;
				minlvl = 5;
			}
			CDboTSClickNPC
			{
				npcidx = 4261101;
			}
			CDboTSCheckClrQst
			{
				and = "422;";
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 42308;
			gtype = 0;
			oklnk = 2;
			area = 42301;
			goal = 42304;
			sort = 42305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 42302;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 42314;
			nextlnk = 254;
			rwdtbl = 42301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4111301;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
	}
}

