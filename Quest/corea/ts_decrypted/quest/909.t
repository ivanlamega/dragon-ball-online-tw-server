CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 909;
	title = 90902;

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
				conv = 90909;
				ctype = 1;
				idx = 5061109;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 90908;
				gtype = 1;
				area = 90901;
				goal = 90904;
				grade = 132203;
				rwd = 100;
				sort = 90905;
				stype = 2;
				taid = 1;
				title = 90902;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 90907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5061109;
			}
			CDboTSCheckLvl
			{
				maxlvl = 40;
				minlvl = 32;
			}
			CDboTSCheckClrQst
			{
				and = "908;";
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
			cont = 90908;
			gtype = 1;
			oklnk = 2;
			area = 90901;
			goal = 90904;
			sort = 90905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 90902;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 90914;
			nextlnk = 254;
			rwdtbl = 90901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3142101;
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

