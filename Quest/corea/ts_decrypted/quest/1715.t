CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1715;
	title = 171502;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 171509;
				ctype = 1;
				idx = 5041115;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 171508;
				gtype = 0;
				area = 171501;
				goal = 171504;
				grade = 132203;
				rwd = 100;
				sort = 171505;
				stype = 2;
				taid = 1;
				title = 171502;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 171507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5041115;
			}
			CDboTSCheckLvl
			{
				maxlvl = 58;
				minlvl = 50;
			}
			CDboTSCheckClrQst
			{
				and = "1712;";
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 171508;
			gtype = 0;
			oklnk = 2;
			area = 171501;
			goal = 171504;
			sort = 171505;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 171502;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 171514;
			nextlnk = 254;
			rwdtbl = 171501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 2611204;
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
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

