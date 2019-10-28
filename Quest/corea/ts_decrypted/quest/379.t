CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 379;
	title = 37902;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSSearchQuest
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
				conv = 37909;
				ctype = 1;
				idx = 4511401;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 37908;
				gtype = 1;
				area = 37901;
				goal = 37904;
				grade = 132203;
				rwd = 100;
				sort = 37905;
				stype = 2;
				taid = 1;
				title = 37902;
			}
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
			desc = 37914;
			nextlnk = 254;
			rwdtbl = 37901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4511401;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 37907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSClickNPC
			{
				npcidx = 4511401;
			}
			CDboTSCheckLvl
			{
				maxlvl = 10;
				minlvl = 2;
			}
			CDboTSCheckClrQst
			{
				and = "206;";
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 37908;
			gtype = 1;
			oklnk = 2;
			area = 37901;
			goal = 37904;
			sort = 37905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 37902;
		}
	}
}

