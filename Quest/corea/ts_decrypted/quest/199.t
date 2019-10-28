CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 199;
	title = 19902;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSItemUpgrade
			{
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 19909;
				ctype = 1;
				idx = 6312102;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 19908;
				gtype = 0;
				area = 19901;
				goal = 19904;
				grade = 132203;
				rwd = 100;
				sort = 19905;
				stype = 1;
				taid = 1;
				title = 19902;
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 19908;
			gtype = 1;
			oklnk = 2;
			area = 19901;
			goal = 19904;
			sort = 19905;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 19902;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 19914;
			nextlnk = 254;
			rwdtbl = 19901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 6312102;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 19907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 6312102;
			}
			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSCheckLvl
			{
				maxlvl = 20;
				minlvl = 10;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "1;0;252;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
	}
}

