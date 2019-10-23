CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 971;
	title = 97102;

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
				conv = 97109;
				ctype = 1;
				idx = 3143102;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 97108;
				gtype = 0;
				area = 97101;
				goal = 97104;
				grade = 132203;
				rwd = 100;
				sort = 97105;
				stype = 2;
				taid = 1;
				title = 97102;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 97107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3143102;
			}
			CDboTSCheckLvl
			{
				maxlvl = 44;
				minlvl = 36;
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
			cont = 97108;
			gtype = 0;
			oklnk = 2;
			area = 97101;
			goal = 97104;
			sort = 97105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 97102;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 97114;
			nextlnk = 254;
			rwdtbl = 97101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4511207;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
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

