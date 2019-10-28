CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1713;
	title = 171302;

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
				conv = 171309;
				ctype = 1;
				idx = 5313202;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 171308;
				gtype = 0;
				area = 171301;
				goal = 171304;
				grade = 132203;
				rwd = 100;
				sort = 171305;
				stype = 1;
				taid = 1;
				title = 171302;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 171307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5313202;
			}
			CDboTSCheckLvl
			{
				maxlvl = 58;
				minlvl = 50;
			}
			CDboTSCheckClrQst
			{
				and = "1711;";
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 171308;
			gtype = 0;
			oklnk = 2;
			area = 171301;
			goal = 171304;
			sort = 171305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 171302;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 171314;
			nextlnk = 254;
			rwdtbl = 171301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 2611204;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
	}
}

